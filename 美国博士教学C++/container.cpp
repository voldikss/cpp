#include <algorithm>
#include <bits/c++config.h>
#include <cassert>
#include <climits>
#include <initializer_list>
#include <iostream>
#include <list>
#include <map>
#include <queue>
#include <set>
#include <stack>
#include <stdexcept>
#include <string>
#include <unordered_map>
#include <variant>
#include <vector>
using namespace std;

class Container {
  private:
    int sz;
    double *elem;

  public:
    virtual double &operator[](int i) const = 0;   // Pure function

    virtual int size() const = 0;

    virtual ~Container() {
    }
};

class Vector {
  private:
    int sz;
    double *elem;

  public:
    Vector(int size) :
        sz(size), elem(new double[size]) {
    }

    Vector(initializer_list<double> list) :
        sz(list.size()),
        elem(new double[list.size()]) {
        int i = 0;
        for (auto &x : list) {
            elem[i] = x;
            i++;
        }
    }

    double &operator[](int i) const {
        return this->elem[i];
    }

    size_t size() const {
        return this->sz;
    }

    ~Vector() {
        delete[] elem;
    }
};

class Vector_Container : public Container {
  private:
    Vector v;

  public:
    Vector_Container(initializer_list<double> vec) :
        v(vec) {
    }

    virtual double &operator[](int i) const override {
        return this->v[i];
    }

    virtual int size() const override {
        return v.size();
    }
};

class List_Container : public Container {
  public:
    List_Container(initializer_list<double> list) {
        for (auto &x : list) {
            lst.push_back(x);
        }
    }

    virtual double &operator[](int i) const override {
        for (auto &x : lst) {
            if (i == 0) return const_cast<double &>(x);
            --i;
        }
        throw out_of_range("List_Container");
    }

    virtual int size() const override {
        return lst.size();
    }

  private:
    list<double> lst;
};

void display(Container &c) {
    for (int i = 0; i < c.size(); i++) {
        cout << c[i] << endl;
    }
}

int main() {
    Vector_Container v{1, 2, 3};
    Container *c1 = &v;

    List_Container l{4, 5, 6};
    Container *c2 = &l;

    display(v);
    display(l);
    return 0;
}
