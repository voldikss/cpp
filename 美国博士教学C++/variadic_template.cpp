/// From: https://www.cnblogs.com/qicosmos/p/4325949.html
#include <initializer_list>
#include <iostream>
#include <utility>
using namespace std;

//----------------------------------------------------------------------------
template <typename T>
void print(T t) {
    cout << t << endl;
}

template <typename T, typename... Args>
void print(T head, Args... rest) {
    cout << head << endl;
    print(rest...);
}
//----------------------------------------------------------------------------

//----------------------------------------------------------------------------
template <typename T>
void printarg(T t) {
    cout << t << endl;
}

template <typename... Args>
void expand(Args... args) {
    int arr[] = {(printarg(args), 0)...};
}
//----------------------------------------------------------------------------

//----------------------------------------------------------------------------
template <typename F, typename... Args>
void expand(F f, Args... args) {
    initializer_list<int>{(f(std::forward<Args>(args)), 0)...};
}

int main() {
    // print("hello", "world");
    // expand("hello", "world");
    // expand([](string s) { cout << s << endl; }, "hello", "world");
    return 0;
}
