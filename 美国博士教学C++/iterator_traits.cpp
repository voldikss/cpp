#include <algorithm>
#include <forward_list>
#include <iostream>
#include <iterator>
#include <list>
#include <vector>

using namespace std;

template <typename C>
using Value_type = typename C::value_type;

template <typename C>
using Iterator_type = typename C::iterator;

template <typename Iter>
using Iterator_catagory = typename std::iterator_traits<Iter>::iterator_category;

template <typename Ran>
void sort_helper(Ran beg, Ran end, random_access_iterator_tag) {
    sort(beg, end);
}

template <typename For>
void sort_helper(For beg, For end, forward_iterator_tag) {
    vector<Value_type<For>> v{beg, end};
    sort(v.begin(), v.end());
    copy(v.begin(), v.end(), beg);
}

template <typename C>
void MySort(C& c) {
    using Iter = Iterator_type<C>;
    sort_helper(begin(c), end(c), Iterator_catagory<Iter>{});
}

void test(vector<string>& v, forward_list<int>& lst) {
    MySort(v);
    MySort(lst);
}

int main(int argc, char* argv[]) {
    vector<string> vec{"voldikss", "hello", "world"};
    forward_list<int> lst{3, 2, 4, 5, 1};
    test(vec, lst);
    for (auto& x : vec)
        cout << x << endl;
    for (auto& x : lst)
        cout << x << endl;
}
