#include <algorithm>
#include <forward_list>
#include <iostream>
#include <iterator>
#include <list>
#include <type_traits>
#include <vector>

using namespace std;

template <typename T>
constexpr bool Is_arthmetic() {
    return std::is_arithmetic<T>::value;
}

template <typename Scalar>
class complex {
    Scalar re, im;

  public:
    static_assert(Is_arthmetic<Scalar>(), "Sorry I only support complex of arithmetic types");
    ///
};

int main(int argc, char* argv[]) {
    cout << Is_arthmetic<int>() << endl;
    complex<int> ci;
    complex<float> cf;
    complex<double> cd;
}
