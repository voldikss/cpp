#include <cstddef>
#include <ext/pool_allocator.h>
#include <iostream>
#include <memory>
#include <vector>

using namespace std;

template <class Alloc>
void cookie_test(Alloc alloc, size_t n) {
    typename Alloc::value_type *p1, *p2, *p3;
    p1 = alloc.allocate(n);
    p2 = alloc.allocate(n);
    p3 = alloc.allocate(n);

    cout << "p1=" << p1 << '\t' << "p2=" << p2 << '\t' << "p3=" << p3 << '\t' << endl;

    alloc.deallocate(p1, sizeof(typename Alloc::value_type));
    alloc.deallocate(p2, sizeof(typename Alloc::value_type));
    alloc.deallocate(p3, sizeof(typename Alloc::value_type));
}

int main(int argc, char* argv[]) {
    cout << sizeof(__gnu_cxx::__pool_alloc<int>) << endl;
    vector<int, __gnu_cxx::__pool_alloc<int>> vecPool1;
    cookie_test(__gnu_cxx::__pool_alloc<double>(), 1);

    cout << "--------------------------------------------------" << endl;

    cout << sizeof(std::allocator<int>) << endl;
    vector<int, std::allocator<int>> vecPool2;
    cookie_test(std::allocator<double>(), 1);

    cout << sizeof(std::allocator<int>) << endl;
    vector<int> vecPool3;
    cookie_test(std::allocator<double>(), 1);

    return 0;
}
