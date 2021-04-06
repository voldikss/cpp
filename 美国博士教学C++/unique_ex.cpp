#include <algorithm>
#include <iostream>
#include <memory>
#include <vector>

using namespace std;

class ResourceType {
  public:
    void foo() {
        cout << "foo called" << endl;
    }
    // ...
    ~ResourceType() {
        cout << "destruct" << endl;
    }
};

using ResourceVector = vector<unique_ptr<ResourceType>>;

int main(int argc, char **argv) {
    // ResourceType *naked_ptr = new ResourceType;

    unique_ptr<ResourceType> r1 = std::make_unique<ResourceType>();
    auto r2 = std::make_unique<ResourceType>();
    unique_ptr<ResourceType> r3 = std::move(r2);
    r2->foo();   // TODO: why ? 在 gdb 中看到 r2 变成 0x0 了，为什么这个调用还能发生？

    ResourceVector vec;
    vec.push_back(std::move(r1));

    return 0;
}
