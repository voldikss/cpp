#include <cstddef>
#include <iostream>
using namespace std;

class Screen {
  public:
    Screen(int x) : i(x){};

    int get() {
        return i;
    }

    void* operator new(size_t size);
    void operator delete(void*, size_t);

  private:
    Screen* next;
    static Screen* freeStore;       // 指向链表头
    static const int screenChunk;   // 数量，多少块

  private:
    int i;
};

Screen* Screen::freeStore = 0;
const int Screen::screenChunk = 24;

void* Screen::operator new(size_t size) {
    Screen* p;
    if (!freeStore) {
        size_t chunk = screenChunk * size;
        freeStore = p = reinterpret_cast<Screen*>(new char[chunk]);
        for (; p != &freeStore[screenChunk - 1]; ++p) {
            p->next = p + 1;
        }
        p->next = nullptr;
    }
    p = freeStore;
    freeStore = freeStore->next;
    return p;
}

void Screen::operator delete(void* p, size_t) {
    static_cast<Screen*>(p)->next = freeStore;
    freeStore = static_cast<Screen*>(p);
}

int main(int argc, char** argv) {
    cout << sizeof(Screen) << endl;

    size_t const N = 100;
    Screen* p[N];

    for (int i = 0; i < N; i++) {
        p[i] = new Screen(i);
    }

    // 这里的自定义实现没带 cookie，所以差值只算对象本身的大小 16 字节
    // 默认的实现带 cookie， 上下 cookie 都有 8 字节，加起来共 16 字节，再加上
    // 对象本身的 16 字节一共 32

    for (int i = 0; i < 10; i++) {
        cout << p[i] << endl;
    }

    for (int i = 0; i < N; i++) {
        delete p[i];
    }
    return 0;
}
