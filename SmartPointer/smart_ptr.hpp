#ifndef SMARTPTR_HPP
#define SMARTPTR_HPP

#include <algorithm>

template <typename T>
class unique_ptr {
  public:
    explicit unique_ptr(T* ptr = nullptr) : ptr_(ptr) {}
    unique_ptr(const unique_ptr&) = delete;
    unique_ptr(unique_ptr&& other) : ptr_(other.release()) {}
    template <typename U>
    unique_ptr(unique_ptr<U>&& other) : ptr_(other.release()) {}
    unique_ptr& operator=(unique_ptr rhs) {
        // rhs 为构造的新对象，在rhs的构造过程中已将原来的 ptr_ 成员
        // 设为 nullptr 了。
        // 此处牵涉到右值引用的自动类型转换，rhs 的构造调用的是移动构
        // 造函数，即相当于 `unique_ptr rhs(std:: move(other))`
        // 而且有了这个则不用再写 `unique_ptr& operator=(const unique_ptr&) = delete`
        // 了因为有了 `unique_ptr(const unique_ptr&) = delete`，则在 rhs
        // 的构造过程中就已经保证了 `p2 = p1` 中 p1 只能为右值引用类型，
        // 太妙了
        rhs.swap(*this);
        return *this;
    }
    // unique_ptr& operator=(const unique_ptr&) = delete;
    ~unique_ptr() { delete ptr_; }

    T& operator*() { return *ptr_; }
    T* operator->() { return ptr_; }
    operator bool() { return ptr_; }

    T* release() {
        T* ptr = ptr_;
        ptr_ = nullptr;
        return ptr;
    }

    void swap(unique_ptr& rhs) { std::swap(ptr_, rhs.ptr_); }

    T* get() const { return ptr_; }

  private:
    T* ptr_;
};

class shared_count {
  public:
    shared_count() : count_(1) {}
    void inc_count() {
        count_++;
    }
    long dec_count() {
        return --count_;
    }
    long get_count() const {
        return count_;
    }

  private:
    long count_;
};

template <typename T>
class shared_ptr {
    template <typename U>
    friend class shared_ptr;

  public:
    explicit shared_ptr(T* ptr = nullptr) : ptr_(ptr) {
        if (ptr) {
            shared_count_ = new shared_count();
        }
    }

    ~shared_ptr() {
        if (ptr_ && !shared_count_->dec_count()) {
            delete ptr_;
            delete shared_count_;
        }
    }

    shared_ptr(const shared_ptr& other) : ptr_(other.ptr_) {
        if (ptr_) {
            shared_count_ = other.shared_count_;
            shared_count_->inc_count();
        }
    }

    shared_ptr(shared_ptr&& other) {
        ptr_ = other.ptr_;
        if (ptr_) {
            shared_count_ = other.shared_count_;
            other.release();
        }
    }

    template <typename U>
    shared_ptr(const shared_ptr<U>& other) : ptr_(other.ptr_) {
        if (ptr_) {
            shared_count_ = other.shared_count_;
            shared_count_->inc_count();
        }
    }

    template <typename U>
    shared_ptr(shared_ptr<U>&& other) : ptr_(other.ptr_) {
        if (ptr_) {
            shared_count_ = other.shared_count_;
            other.ptr_ = nullptr;
        }
    }

    template <typename U>
    shared_ptr(const shared_ptr<U>& other, T* ptr) : ptr_(ptr) {
        if (ptr_) {
            shared_count_ = other.shared_count_;
            shared_count_->inc_count();
        }
    }

    // 囊括了许多
    shared_ptr& operator=(shared_ptr rhs) {
        rhs.swap(*this);
        return *this;
    }

    T& operator*() { return *ptr_; }
    T* operator->() { return ptr_; }
    operator bool() { return ptr_; }

    T* get() const { return ptr_; }

    void swap(shared_ptr& rhs) {
        std::swap(ptr_, rhs.ptr_);
        std::swap(shared_count_, rhs.shared_count_);
    }

    T* release() {
        ptr_ = nullptr;
        shared_count_ = nullptr;
    }

    long use_count() {
        if (ptr_) {
            return shared_count_->get_count();
        } else {
            return 0;
        }
    }

  private:
    T* ptr_;
    shared_count* shared_count_;
};

// lvalue ref
template <typename U, typename V>
shared_ptr<U> static_pointer_cast(const shared_ptr<V>& other) noexcept {
    using Sp = shared_ptr<U>;
    if (auto* ptr = static_cast<U*>(other.get()))
        return Sp(other, ptr);
    return Sp();
}

template <typename U, typename V>
shared_ptr<U> dynamic_pointer_cast(const shared_ptr<V>& other) noexcept {
    using Sp = shared_ptr<U>;
    if (auto* ptr = dynamic_cast<U*>(other.get()))
        return Sp(other, ptr);
    return Sp();
}

template <typename U, typename V>
shared_ptr<U> const_pointer_cast(const shared_ptr<V>& other) noexcept {
    using Sp = shared_ptr<U>;
    if (auto* ptr = const_cast<U*>(other.get()))
        return Sp(other, ptr);
    return Sp();
}

template <typename U, typename V>
shared_ptr<U> reinterpret_pointer_cast(const shared_ptr<V>& other) noexcept {
    using Sp = shared_ptr<U>;
    if (auto* ptr = reinterpret_cast<U*>(other.get()))
        return Sp(other, ptr);
    return Sp();
}

// rvalue ref version
template <typename U, typename V>
shared_ptr<U> static_pointer_cast(const shared_ptr<V>&& other) noexcept {
    using Sp = shared_ptr<U>;
    if (auto* ptr = static_cast<U*>(other.get()))
        return Sp(std::move(other), ptr);
    return Sp();
}

template <typename U, typename V>
shared_ptr<U> dynamic_pointer_cast(const shared_ptr<V>&& other) noexcept {
    using Sp = shared_ptr<U>;
    if (auto* ptr = dynamic_cast<U*>(other.get()))
        return Sp(std::move(other), ptr);
    return Sp();
}

template <typename U, typename V>
shared_ptr<U> const_pointer_cast(const shared_ptr<V>&& other) noexcept {
    using Sp = shared_ptr<U>;
    if (auto* ptr = const_cast<U*>(other.get()))
        return Sp(std::move(other), ptr);
    return Sp();
}

template <typename U, typename V>
shared_ptr<U> reinterpret_pointer_cast(const shared_ptr<V>&& other) noexcept {
    using Sp = shared_ptr<U>;
    if (auto* ptr = reinterpret_cast<U*>(other.get()))
        return Sp(std::move(other), ptr);
    return Sp();
}

#endif /* !SMARTPTR_HPP */
