#include "cstring.h"

#include <algorithm>

size_t Strlen(const char* str) {
    const char* end = str;
    while (*end) {
        end++;
    }
    return end - str;
}

int Strcmp(const char* first, const char* second) {
    while (*first && (*first == *second)) {
        first++;
        second++;
    }
    return static_cast<int>(*first) - static_cast<int>(*second);
}

int Strncmp(const char* first, const char* second, size_t count) {
    while (count && *first && (*first == *second)) {
        first++;
        second++;
        count--;
    }
    if (count == 0) {
        return 0;
    }
    return static_cast<int>(*first) - static_cast<int>(*second);
}

char* Strcpy(char* dest, const char* src) {
    char* result = dest;
    while ((*dest++ = *src++)) {
    }
    return result;
}

char* Strncpy(char* dest, const char* src, size_t count) {
    char* result = dest;
    while (count && (*dest++ = *src++)) {
        count--;
    }
    while (count--) {
        *dest++ = '\0';
    }
    return result;
}

char* Strcat(char* dest, const char* src) {
    char* result = dest;
    while (*dest) {
        dest++;
    }
    while ((*dest++ = *src++)) {
    }
    return result;
}

char* Strncat(char* dest, const char* src, size_t count) {
    char* result = dest;
    while (*dest) {
        dest++;
    }
    while (count && (*dest++ = *src++)) {
        count--;
    }
    if (count == 0) {
        *dest = '\0';
    }
    return result;
}

const char* Strchr(const char* str, char symbol) {
    const char* last = str;
    const size_t length = Strlen(str);
    for (size_t i = 0; i < length + 1; ++i) {
        if (*last == symbol) {
            return last;
        }
        ++last;
    }
    return nullptr;
}

const char* Strrchr(const char* str, char symbol) {
    const char* last = nullptr;
    while (*str) {
        if (*str == symbol) {
            last = str;
        }
        str++;
    }
    if (*str == symbol) {
        return str;
    }
    return last;
}

size_t Strspn(const char* dest, const char* src) {
    size_t count = 0;
    while (*dest && Strchr(src, *dest)) {
        dest++;
        count++;
    }
    return count;
}

size_t Strcspn(const char* dest, const char* src) {
    size_t count = 0;
    while (*dest && !Strchr(src, *dest)) {
        dest++;
        count++;
    }
    return count;
}

const char* Strpbrk(const char* dest, const char* breakset) {
    while (*dest) {
        if (Strchr(breakset, *dest)) {
            return dest;
        }
        dest++;
    }
    return nullptr;
}

const char* Strstr(const char* str, const char* pattern) {
    if (*pattern == '\0') {
        return str;
    }
    while (*str) {
        const char* p = pattern;
        const char* s = str;
        while (*p && (*p == *s)) {
            p++;
            s++;
        }
        if (*p == '\0') {
            return str;
        }
        str++;
    }
    return nullptr;
}