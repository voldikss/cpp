#include <algorithm>
#include <bitset>
#include <cassert>
#include <climits>
#include <cmath>
#include <iostream>
#include <list>
#include <map>
#include <numeric>
#include <queue>
#include <set>
#include <stack>
#include <string>
#include <unordered_map>
#include <vector>
using namespace std;

class Obj1 {
  public:
    Obj1() {
        cout << "Obj1()" << endl;
    }
    Obj1(const Obj1&) {
        cout << "Obj1(const Obj1&)" << endl;
    }
    Obj1(Obj1&&) {
        cout << "Obj1(Obj1&&)" << endl;
    }
};

class Obj2 {

  public:
    Obj2() {
        cout << "Obj2()" << endl;
    }
    Obj2(const Obj2&) {
        cout << "Obj2(const Obj2&)" << endl;
    }

    // NOTE
    // https://www.zhihu.com/question/30950837
    // noexcept最有用的地方是用在move constructor和move assignment上，你的move
    // 操作如果不是noexcept的，很多情况下即使逻辑上可以move，编译器也会执行copy。

    // NOTE
    // https://github.com/OXygenPanda/1.CPP_in_depth/blob/main/modern_C%2B%2B/04-%E5%AE%B9%E5%99%A8I.md
    // 当 push_back, insert, reverse, resize等函数导致内存重新分配时或当 insert,
    // erase导致元素位置移动时，vector试图把元素 move 到新的内存区域。由于
    // vector保证强异常安全性，如果元素没有提供一个保证不抛异常到移动构造函数，
    // vector通常会使用拷贝构造函数。因此，对于拷贝代价较高的自定义元素类型，我
    // 们应当定义移动构造函数并标记为 noexcept，或只在容器中放对象的智能指针。
    Obj2(Obj2&&) noexcept {
        cout << "Obj2(Obj2&&)" << endl;
    }
};

int main(int argc, char** argv) {
    vector<Obj1> v1;
    v1.reserve(2);
    v1.emplace_back();
    v1.emplace_back();
    v1.emplace_back();

    vector<Obj2> v2;
    v2.reserve(2);
    v2.emplace_back();
    v2.emplace_back();
    v2.emplace_back();
}
