#include <algorithm>
#include <cassert>
#include <climits>
#include <iostream>
#include <iterator>
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

int main(int argc, char **argv) {
    vector<string> quote{"This", "is", "a", "C++", "class"};
    vector<string> res;
    std::transform(begin(quote), end(quote), back_inserter(res),
                   [](const string &word) {
                       return "<" + word + ">";
                   });
    std::for_each(begin(res), end(res),
                  [](const string &word) {
                      cout << word << " ";
                  });
}
