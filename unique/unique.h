#pragma once

#include <algorithm>

template <typename T>
T Unique(T begin, T end) {
    if (begin == end) {
        return end;
    }
    T result = begin;
    T current = begin;
    ++current;
    while (current != end) {
        if (*current != *result) {
            ++result;
            if (result != current) {
                *result = std::move(*current);
            }
        }
        ++current;
    }
    return ++result;
}