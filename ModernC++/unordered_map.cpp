#include <algorithm>
#include <cassert>
#include <climits>
#include <iostream>
#include <iterator>
#include <list>
#include <map>
#include <memory>
#include <queue>
#include <set>
#include <stack>
#include <string>
#include <string_view>
#include <type_traits>
#include <unordered_map>
#include <vector>
using namespace std;

class Obj1 {
  public:
    int a;
};

namespace std {
template <>
struct hash<Obj1> {
    size_t operator()(const Obj1& o) const noexcept {
        // ...
    }
};
}   // namespace std

// NOTE 底层是哈希表的容器如果元素类型是自定义类型，需要为该类型写一个 hash 特化版本。
// 一般情况下，向 std 命名空间增加内容是禁止的，属于未定义行为。以上是一种特殊
// 情况。使用，priority或有序关联容器，增删改查的时间复杂度是 O(logn), 而无序关
// 联容器的时间复杂度是 O(1)，前提是有很好的哈希函数。无序关联容器的最坏时间复
// 杂度是 O(n)。

int main(int argc, char** argv) {
    unordered_map<Obj1, string> kv;
}
