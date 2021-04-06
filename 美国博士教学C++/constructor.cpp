#include <cstddef>
#include <initializer_list>
#include <iostream>
#include <utility>
using namespace std;

class Vector {
  private:
    size_t sz;
    double *elem;

  public:
    Vector(initializer_list<double> lst) :
        sz(lst.size()),
        elem(new double[lst.size()]) {
        int i = 0;
        for (auto &x : lst) {
            elem[i] = x;
            i++;
        }
    }

    Vector(int size) :
        sz(size),
        elem(new double(size)) {
    }

    //----------------------------------------------------------------------------
    Vector(const Vector &V) :
        sz(V.sz),
        elem(new double(V.sz)) {
        cout << "Copy Constructor" << endl;
        for (int i = 0; i < V.sz; i++) {
            elem[i] = V.elem[i];
        }
    }

    Vector(Vector &&V) :
        sz(V.sz),
        elem(V.elem) {
        cout << "Move constructor" << endl;
        V.elem = nullptr;
        V.sz = 0;
    }

    //----------------------------------------------------------------------------
    Vector &operator=(const Vector &V) {
        cout << "Copy Assignment" << endl;
        double *p = new double(V.sz);
        for (int i = 0; i < V.sz; i++) {
            p[i] = V.elem[i];
        }
        delete[] elem;
        elem = p;
        sz = V.sz;
        return *this;
    }

    Vector &operator=(Vector &&V) {
        cout << "Move Assignment" << endl;
        sz = V.sz;
        elem = V.elem;
        V.elem = nullptr;
        V.sz = 0;
        return *this;
    }

    //----------------------------------------------------------------------------
    ~Vector() {
    }

    double &operator[](size_t i) {
        return elem[i];
    }
};

int main() {
    Vector A(3);
    // Vector B(A);
    Vector B = A;
    // B = A;
    Vector C(3);
    C = A;
    Vector D = std::move(A);
    Vector E(3);
    D = std::move(A);
}
