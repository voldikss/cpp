#include <cassert>
#include <cstddef>
#include <cstdlib>
#include <iostream>
#include <string>

#define DECLARE_POOL_ALLOC()                                                    \
  public:                                                                       \
    void* operator new(size_t size) { return myAlloc.allocate(size); }          \
    void operator delete(void* p, size_t size) { myAlloc.deallocate(p, size); } \
                                                                                \
  protected:                                                                    \
    static allocator myAlloc;

#define IMPLEMENT_POOL_ALLOC(class_name) \
    allocator class_name::myAlloc;

class allocator {
  private:
    struct obj {
        struct obj* next;
    };

  public:
    void* allocate(size_t);
    void deallocate(void*, size_t);

  private:
    obj* freeStore = nullptr;
    const int CHUNK = 5;
};

// size 是要分配对象的大小，e.g. Foo
// obj 只是一个链表指针
void* allocator::allocate(size_t size) {
    obj* p;
    // sizeof(obj) != size; !!!

    if (!freeStore) {
        size_t chunk = CHUNK * size;
        freeStore = p = (obj*)malloc(chunk);

        for (int i = 0; i < (CHUNK - 1); i++) {
            p->next = (obj*)((char*)p + size);   // TODO
            p = p->next;
        }
        p->next = nullptr;
    }

    p = freeStore;
    freeStore = freeStore->next;
    return p;
}

void allocator::deallocate(void* p, size_t size) {
    ((obj*)p)->next = freeStore;
    freeStore = (obj*)p;
}

class Foo {
    DECLARE_POOL_ALLOC()

  public:
    long L;
    std::string str;

  public:
    Foo(long l) : L(l) {}
};
IMPLEMENT_POOL_ALLOC(Foo)

int main(int argc, char* argv[]) {
    Foo* p[100];
    std::cout << sizeof(Foo) << std::endl;

    for (int i = 0; i < 23; i++) {
        p[i] = new Foo(i);
        std::cout << p[i] << ' ' << p[i]->L << std::endl;
    }

    for (int i = 0; i < 23; i++) {
        delete p[i];
    }

    return 0;
}
