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

class A {
  public:
    void foo() {
        cout << "foo" << endl;
    }
};

class B : virtual public A {
};

class C : virtual public A {
};

class D : public B, public C {
};

int main() {
    D d;
    d.foo();
    return 0;
}
