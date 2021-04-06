#include <cassert>
#include <cstddef>
#include <iostream>
#include <new>
using namespace std;

class Airplane {
  private:
    struct AirplaneRep {
        unsigned long miles;
        char type;
    };

    union {
        AirplaneRep rep;
        Airplane* next;
    };

  public:
    unsigned long getMiles() {
        return rep.miles;
    }

    char getType() {
        return rep.type;
    }

    void set(unsigned long m, char t) {
        rep.miles = m;
        rep.type = t;
    }

    static void* operator new(size_t);
    static void operator delete(void*, size_t);

  private:
    static const int BLOCK_SIZE;
    static Airplane* headOfFreeList;
};

const int Airplane::BLOCK_SIZE = 512;
Airplane* Airplane::headOfFreeList = nullptr;

void* Airplane::operator new(size_t size) {
    if (size != sizeof(Airplane))
        return ::operator new(size);

    Airplane* p = headOfFreeList;
    if (p) {
        headOfFreeList = p->next;
    } else {
        Airplane* newBlock = static_cast<Airplane*>(::operator new(BLOCK_SIZE * sizeof(Airplane)));

        for (int i = 1; i < BLOCK_SIZE; i++) {
            newBlock[i].next = &newBlock[i + 1];
        }
        newBlock[BLOCK_SIZE - 1].next = nullptr;
        p = newBlock;
        headOfFreeList = &newBlock[1];
    }
    return p;
}

void Airplane::operator delete(void* p, size_t size) {
    if (!p) return;
    if (size != sizeof(Airplane)) {
        ::operator delete(p);
        return;
    }

    Airplane* carcass = static_cast<Airplane*>(p);
    carcass->next = headOfFreeList;
    headOfFreeList = carcass;
}

int main(int argc, char* argv[]) {
    cout << sizeof(Airplane) << endl;

    size_t const N = 100;
    Airplane* p[N];

    for (int i = 0; i < N; i++) {
        p[i] = new Airplane;
        p[i]->set(i, i);
        assert(p[i]->getMiles() == i);
        assert(p[i]->getType() == i);
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
