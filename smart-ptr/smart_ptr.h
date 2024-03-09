#pragma once

#include <string>

template <class T>
class WeakPtr;

template <class T>
class SharedPtr {
public:
    SharedPtr(const WeakPtr<T>& rhs);
};

template <class T>
class WeakPtr {
public:
};

template <class T>
SharedPtr<T>::SharedPtr(const WeakPtr<T>& rhs) {
}
