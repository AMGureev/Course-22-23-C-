#pragma once

template <class Iterator, class T>
Iterator FindLast(Iterator first, Iterator last, const T& val) {
    auto copy_last = last;
    while (first != last) {
        --last;
        if (*last == val) {
            return last;
        }
    }
    return copy_last;
}