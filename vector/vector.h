#pragma once

#include <algorithm>
#include <cstddef>
#include <initializer_list>
#include <iterator>

template <class T>
class Vector {
public:
    class Iterator : public std::iterator<std::random_access_iterator_tag, T> {
    public:
        Iterator() : ptr_(nullptr) {
        }

        explicit Iterator(T* ptr) : ptr_(ptr) {
        }

        T& operator*() const {
            return *ptr_;
        }

        Iterator& operator++() {
            ++ptr_;
            return *this;
        }

        Iterator operator++(int) {
            Iterator temp = *this;
            ++ptr_;
            return temp;
        }

        Iterator& operator--() {
            --ptr_;
            return *this;
        }

        Iterator operator--(int) {
            Iterator temp = *this;
            --ptr_;
            return temp;
        }

        Iterator operator+(int n) const {
            return Iterator(ptr_ + n);
        }

        Iterator operator-(int n) const {
            return Iterator(ptr_ - n);
        }

        Iterator& operator+=(int n) {
            ptr_ += n;
            return *this;
        }

        Iterator& operator-=(int n) {
            ptr_ -= n;
            return *this;
        }

        bool operator==(const Iterator& other) const {
            return ptr_ == other.ptr_;
        }

        bool operator!=(const Iterator& other) const {
            return ptr_ != other.ptr_;
        }

        bool operator<(const Iterator& other) const {
            return ptr_ < other.ptr_;
        }

        bool operator>(const Iterator& other) const {
            return ptr_ > other.ptr_;
        }

        bool operator<=(const Iterator& other) const {
            return ptr_ <= other.ptr_;
        }

        bool operator>=(const Iterator& other) const {
            return ptr_ >= other.ptr_;
        }

        int operator-(const Iterator& other) const {
            return ptr_ - other.ptr_;
        }

        T& operator[](int n) const {
            return *(ptr_ + n);
        }

        T* operator->() const {
            return ptr_;
        }

    private:
        T* ptr_;
    };

    Vector() : size_(0), capacity_(0), data_(nullptr) {
    }

    explicit Vector(size_t size) : size_(size), capacity_(size) {
        data_ = new T[capacity_]{};
    }

    Vector(std::initializer_list<T> values) : size_(values.size()), capacity_(values.size()) {
        data_ = new T[capacity_];
        std::copy(values.begin(), values.end(), data_);
    }

    Vector(const Vector& other) : size_(other.size_), capacity_(other.capacity_) {
        data_ = new T[capacity_];
        std::copy(other.data_, other.data_ + size_, data_);
    }

    Vector(Vector&& other) noexcept : size_(other.size_), capacity_(other.capacity_), data_(other.data_) {
        other.size_ = 0;
        other.capacity_ = 0;
        other.data_ = nullptr;
    }

    Vector& operator=(const Vector& other) {
        if (this != &other) {
            Vector temp(other);
            Swap(temp);
        }
        return *this;
    }

    Vector& operator=(Vector&& other) noexcept {
        if (this != &other) {
            Clear();
            delete[] data_;
            size_ = other.size_;
            capacity_ = other.capacity_;
            data_ = other.data_;
            other.size_ = 0;
            other.capacity_ = 0;
            other.data_ = nullptr;
        }
        return *this;
    }

    ~Vector() {
        delete[] data_;
    }

    void Swap(Vector& other) {
        std::swap(size_, other.size_);
        std::swap(capacity_, other.capacity_);
        std::swap(data_, other.data_);
    }

    T& operator[](size_t index) {
        return data_[index];
    }

    const T& operator[](size_t index) const {
        return data_[index];
    }

    size_t Size() const {
        return size_;
    }

    size_t Capacity() const {
        return capacity_;
    }

    void PushBack(const T& value) {
        if (size_ == capacity_) {
            size_t new_capacity = (capacity_ == 0) ? 1 : capacity_ * 2;
            T* new_data = new T[new_capacity];
            std::copy(data_, data_ + size_, new_data);
            delete[] data_;
            data_ = new_data;
            capacity_ = new_capacity;
        }
        data_[size_] = value;
        ++size_;
    }

    void PopBack() {
        if (size_ > 0) {
            --size_;
        }
    }

    void Clear() {
        size_ = 0;
    }

    void Reserve(size_t capacity) {
        if (capacity > capacity_) {
            T* new_data = new T[capacity];
            std::copy(data_, data_ + size_, new_data);
            delete[] data_;
            data_ = new_data;
            capacity_ = capacity;
        }
    }

    Iterator Begin() {
        return Iterator(data_);
    }

    const Iterator Begin() const {
        return Iterator(data_);
    }

    Iterator End() {
        return Iterator(data_ + size_);
    }

    const Iterator End() const {
        return Iterator(data_ + size_);
    }

    Iterator begin() {  // NOLINT
        return Begin();
    }

    Iterator end() {  // NOLINT
        return End();
    }

private:
    size_t size_;
    size_t capacity_;
    T* data_;
};
