#include <iostream>

using namespace std;

template <size_t N>
struct Fib {
    static constexpr const size_t value = Fib<N - 1>::value + Fib<N - 2>::value;
};

template <>
struct Fib<1> {
    static constexpr const size_t value = 1;
};

template <>
struct Fib<0> {
    static constexpr const size_t value = 0;
};

int main(int argc, char* argv[]) {
    auto res = Fib<10>::value;
    cout << res << endl;
}
