#include <algorithm>
#include <cassert>
#include <climits>
#include <exception>
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

class MyException : public exception {
  public:
    string msg() const {
        return "my exception";
    }
};

int main(int argc, char **argv) {
    try {
        std::overflow_error("ddd");
    } catch (MyException e) {
        cout << e.msg(); 
    }
    return 0;
}
