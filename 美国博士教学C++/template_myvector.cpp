#include <cstddef>
#include <initializer_list>
#include <iostream>

template <typename T>
class Vector {
  public:
    explicit Vector(size_t size);

    Vector(const Vector &other);

    Vector(std::initializer_list<T> lst);

    ~Vector();

    const T &operator[](size_t i) const;

    size_t size();

  private:
    size_t sz;
    T *elem;
};

template <typename T>
Vector<T>::Vector(size_t size) {
    elem = new T[size];
    sz = size;
}

template <typename T>
Vector<T>::Vector(const Vector<T> &other) {
}

template <typename T>
Vector<T>::Vector(std::initializer_list<T> lst) {
    sz = lst.size();
    elem = new T[sz];
    auto iter = lst.begin();
    size_t cnt = 0;
    while (iter != lst.end()) {
        elem[cnt] = *iter;
        ++iter;
        ++cnt;
    }
}

template <typename T>
Vector<T>::~Vector() {
    delete[] elem;
}

template <typename T>
const T &Vector<T>::operator[](size_t i) const {
    return elem[i];
}

template <typename T>
size_t Vector<T>::size() {
    return sz;
}

int main(int argc, char *argv[]) {
    Vector<int> v{1, 2, 3, 4};
    for (size_t i = 0; i < v.size(); ++i) {
        std::cout << v[i] << std::endl;
    }
    return 0;
}
