#include <algorithm>
#include <iostream>
#include <memory>

using namespace std;

int main(int argc, char *argv[]) {
    string name = "nynagnz";
    string gender = "male";
    auto square = [=, &name ](const int &x) {
        name = "voldikss";
        cout << name << endl;
        cout << gender << endl;
        return x * x;
    };
    cout << square(3) << endl;
}
