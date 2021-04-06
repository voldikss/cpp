#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

class A {
  public:
    A() {
        x = 0;
        cout << "A()" << endl;
    }
    A(int x_arg, string s_arg) : x(x_arg), s(s_arg) {
        cout << "A(x_arg)" << endl;
    }
    explicit A(const A &rhs) {
        x = rhs.x;
        cout << "A(const A &rhs)" << endl;
    }
    explicit A(A &&rhs) {
        x = rhs.x;
        cout << "A(A &&rhs)" << endl;
    }
    // ~A() {
    //     cout << "desctruct" << endl;
    // }

  private:
    int x;
    string s;
};

int main() {
    {
        vector<A> v;
        cout << "call emplace_back" << endl;
        v.emplace_back(3, "hello");
    }
    {
        vector<A> v;
        cout << "call push_back" << endl;
        v.push_back(A(3, "hello"));
    }
    return 0;
}


/// For more
/// - https://zhuanlan.zhihu.com/p/183861524
