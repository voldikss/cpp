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

class Base {
  public:
    virtual void foo() {
        cout << "foo_Base" << endl;
    }

    virtual ~Base() {
        cout << "destruct_Base" << endl;
    }
};

class Derived : public Base {
  public:
    virtual void foo() {
        cout << "foo_Derived" << endl;
    }

    virtual ~Derived() {
        cout << "destruct_Derived" << endl;
    }
};

int main() {
    // Derived d1;
    // Base *b1 = &d1;
    // b1->foo();
    Base *b1 = new Derived;
    delete b1;
}
