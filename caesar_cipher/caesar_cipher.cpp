#include "caesar_cipher.h"

std::string Decipher(const std::string& cipher, size_t shift) {
    std::string plain;
    const int64_t alphabet_size = 26;
    for (size_t i = 0; i < cipher.size(); ++i) {
        char c = cipher[i];
        if (std::isalpha(c)) {
            char base = std::isupper(c) ? 'A' : 'a';
            c = static_cast<char>((c - base - shift + alphabet_size) % alphabet_size + base);
        }
        plain += c;
    }
    return plain;
}
