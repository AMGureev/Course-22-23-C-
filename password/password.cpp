#include "password.h"

bool ValidatePassword(const std::string& password) {
    const int64_t first = 8;
    const int64_t second = 14;
    if (password.length() < first || password.length() > second) {
        return false;
    }
    bool has_upper = false;
    bool has_lower = false;
    bool has_digit = false;
    bool has_special = false;
    const int64_t third = 33;
    const int64_t fourth = 126;
    for (char ch : password) {
        if (ch >= third && ch <= fourth) {
            if (std::isupper(ch)) {
                has_upper = true;
            } else if (std::islower(ch)) {
                has_lower = true;
            } else if (std::isdigit(ch)) {
                has_digit = true;
            } else {
                has_special = true;
            }
        } else {
            return false;
        }
    }
    int64_t count = 0;
    if (has_upper) {
        count++;
    }
    if (has_lower) {
        count++;
    }
    if (has_digit) {
        count++;
    }
    if (has_special) {
        count++;
    }
    return count >= 3;
}
