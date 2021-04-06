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

enum Week {
    Monday,
    Tuesday,
    Wednesday = 100,
    Thursday,
    Friday,
    Saturday,
    Sunday,
} Weekday;

enum class Month : unsigned {
    January,
};

int main() {
    cout << Week::Monday << endl;
    cout << Week::Tuesday << endl;
    cout << Week::Wednesday << endl;
    cout << Week::Thursday << endl;
    cout << Week::Friday << endl;
    cout << Week::Saturday << endl;
    cout << Week::Sunday << endl;
    cout << Weekday << endl;
    // Weekday = 102;       // Error
    // Weekday = Friday;    // OK
    cout << Weekday << endl;
    cout << (Week::Monday == 0) << endl;
    cout << (Month::January == 0) << endl;
    return 0;
}
