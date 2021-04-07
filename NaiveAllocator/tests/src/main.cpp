#include "NaiveAllocator.hpp"
#include <iostream>
#include <vector>

int main(int argc, char** argv) {
    std::vector<int, NaiveAllocator<int>> v(0);
    for (int i = 0; i < 30; ++i) {
        v.push_back(i);
        std::cout << "当前容器占用量：" << v.get_allocator().get_alloc_count() << std::endl;
    }
    return 0;
}
