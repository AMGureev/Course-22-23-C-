#pragma once

template <typename T>
T IsSortedUntil(T begin, T end) {
    if (begin == end) {
        return end;
    }
    T next = begin;
    ++next;
    while (next != end) {
        if (*next < *begin) {
            return next;
        }
        ++begin;
        ++next;
    }
    return end;
}