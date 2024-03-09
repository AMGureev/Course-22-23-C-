#pragma once

template <typename T, typename U>
T Remove(T begin, T end, U value) {
    T result = begin;
    while (begin != end) {
        if (*begin != value) {
            *result = *begin;
            ++result;
        }
        ++begin;
    }
    return result;
}