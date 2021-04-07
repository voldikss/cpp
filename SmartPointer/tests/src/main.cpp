#include "SmartPointer.hpp"
#include <cassert>
#include <iostream>

using namespace std;

class animal {
  public:
    animal() = default;
    ~animal() {
        // cout << "deconstructor" << endl;
    }
};
class dog : public animal {};
class cat : public animal {};

void test_unique() {
    dog* p = new dog;
    unique_ptr<dog> p1(p);
    unique_ptr<animal> p2;
    p2 = std::move(p1);
}

void test_shared() {
    shared_ptr<dog> p1(new dog);
    assert(p1.use_count() == 1);
    // copy construct
    {
        shared_ptr<animal> p2(p1);
        assert(p1.use_count() == 2);
        assert(p2.use_count() == 2);
    }
    // move construct
    assert(p1.use_count() == 1);
    {
        shared_ptr<animal> p3(std::move(p1));
        assert(p1.use_count() == 0);
        assert(p3.use_count() == 1);
    }
    assert(p1.use_count() == 0);

    // cast
    shared_ptr<dog> p4(new dog);
    shared_ptr<animal> p5 = dynamic_pointer_cast<animal>(p4);
    assert(p5.use_count() == 2);

    // copy assignment
    shared_ptr<dog> p6(new dog);
    shared_ptr<animal> p7;
    p7 = p6;
    assert(p7.use_count() == 2);

    // copy assignment
    shared_ptr<dog> p8(new dog);
    shared_ptr<animal> p9;
    p9 = std::move(p8);
    assert(p9.use_count() == 1);
}

int main(int argc, char* argv[]) {
    test_unique();
    test_shared();
    return 0;
}
