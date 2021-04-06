#include <algorithm>
#include <cassert>
#include <climits>
#include <iostream>
#include <list>
#include <map>
#include <queue>
#include <set>
#include <stack>
#include <string>
#include <unordered_map>
#include <variant>
#include <vector>
using namespace std;

void f(string &&s) {

}

int main(int argc, char **argv) {
    vector<string> sv;
    string str = "hello";
    // 点进去看，这两个 push_back 的实现不同 
    sv.push_back(str); // copy
    sv.push_back(std::move(str)); // move
    sv.push_back("hello"); // move

    /// More in https://www.zhihu.com/question/64205844
    // std::move 并不会真正地移动对象，真正的移动操作是在移动构造函数、移动赋
    // 值函数等完成的，std::move 只是将参数转换为右值引用而已（相当于一个
    // static_cast）。
    /// 因此这样看来，move 这个名字并不太恰当
    string s = "hello";
    string &&rr = std::move(s); // s 仍然有效，并没有被移动，只是定义了一个指向 s 的右值引用，并未调用移动构造函数
    string r = std::move(s); // s 被移动了，因为这里调用了 string 的移动构造函数
    cout << s << endl;
}
