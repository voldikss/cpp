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

enum Type {
    str,
    num,
};

// struct Entry {
//     char *name;
//     Type t;
//     char *s;
//     int i;
// };

// void f(Entry *p) {
//     if (p->t == str) {
//         cout << p->s << endl;
//     } else if (p->t == num) {
//         cout << p->i << endl;
//     }
// }

union Value {
    char *s;
    int i;
};

struct Entry {
    char *name;
    Type t;
    Value v;
};

void f(Entry *p) {
    if (p->t == str) {
        cout << p->v.s << endl;
    } else if (p->t == num) {
        cout << p->v.i << endl;
    }
}

int main() {
    // Entry info1{
    //     .name = "gender",
    //     .t = str,
    //     .s = "male"};
    // Entry info2{
    //     .name = "height",
    //     .t = num,
    //     .i = 175};

    Entry info1{
        .name = "gender",
        .t = str,
        .v = {
            .s = "male",
        },
    };
    Entry info2{
        .name = "height",
        .t = num,
        .v = {
            .i = 175,
        },
    };

    f(&info1);
    f(&info2);
    return 0;
}
