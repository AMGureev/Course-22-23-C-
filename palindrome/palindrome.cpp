#include "palindrome.h"

bool IsPalindrome(const std::string& str) {
    int64_t left = 0;
    int64_t right = static_cast<int64_t>(str.length()) - 1;
    while (left < right) {
        while (left < right && str[left] == ' ') {
            ++left;
        }
        while (left < right && str[right] == ' ') {
            --right;
        }
        if (left < right && str[left] != str[right]) {
            return false;
        }
        ++left;
        --right;
    }
    return true;
}