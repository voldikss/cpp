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
    static void printHW() {
        cout << "Hello World" << endl;
    }
};

int main() {
    Vector A;
    A.printHW();
    Vector::printHW();
}
