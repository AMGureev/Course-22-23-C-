#pragma once

template <typename T, typename U>
U Copy(T src_begin, T src_end, U dest) {
    while (src_begin != src_end) {
        *dest = *src_begin;
        ++src_begin;
        ++dest;
    }
    return dest;
}

template <typename T, typename U>
U CopyBackward(T src_begin, T src_end, U dest) {
    T src_curr = src_end;
    U dest_curr = dest;

    while (src_curr != src_begin) {
        --src_curr;
        --dest_curr;
        *dest_curr = *src_curr;
    }
    return dest_curr;
}