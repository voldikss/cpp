#pragma once
#include <bits/c++config.h>
#include <cstdlib>
#include <iostream>
#include <limits>
#include <new>
#include <utility>

template <class T>
class NaiveAllocator {
  public:
    using value_type = T;

    using pointer = T*;
    using const_pointer = const T*;

    using void_pointer = void*;
    using const_void_pointer = const void*;

    using reference = T&;
    using const_reference = const T&;

    using size_type = std::size_t;
    using difference_type = std::ptrdiff_t;

    NaiveAllocator() = default;
    NaiveAllocator(const NaiveAllocator&) = default;
    template <typename U>
    NaiveAllocator(const NaiveAllocator<U>&) {}
    ~NaiveAllocator() = default;

    template <class U>
    struct rebind {
        using other = NaiveAllocator<U>;
    };

    pointer allocate(size_type n) {
        alloc_count += n;
        pointer ptr = static_cast<pointer>(::operator new(sizeof(T) * n));
        if (ptr == nullptr) {
            std::cout << "Allocation failed: out of memory" << std::endl;
            exit(1);
        }
        return ptr;
    }

    pointer allocate(size_type n, const_void_pointer hint) {
        alloc_count -= n;
        return this->allocate(n);
    }

    void deallocate(pointer p, size_type n) {
        ::operator delete(p);
    }

    size_type get_alloc_count() const {
        return alloc_count;
    }

    size_type max_size() const {
        return std::numeric_limits<size_type>::max() / sizeof(T);
    }

    pointer address(reference x) const {
        return &x;
    }

    pointer address(const_reference x) const {
        return &x;
    }

    template <class U, class... Args>
    void constructor(U* p, Args&&... args) {
        new (p) U(std::forward<Args>(args)...);
    }

    template <class U, class... Args>
    void destroy(U* p) {
        p->~U();
    }

  private:
    size_type alloc_count;
};

template <class U, class V>
bool operator==(const NaiveAllocator<U>&, const NaiveAllocator<V>&) {
    return true;
}

template <class U, class V>
bool operator!=(const NaiveAllocator<U>&, const NaiveAllocator<V>&) {
    return false;
}
