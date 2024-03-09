#pragma once

#include <cassert>
#include <iostream>
#include <memory>
#include <string>
#include <vector>

#include "reader.h"

class LimitReader : public Reader {
private:
    Reader* reader;
    size_t limit;
    size_t bytesRead;

public:
    LimitReader(Reader* r, size_t l) : reader(r), limit(l), bytesRead(0) {
    }

    size_t Read(char* buf, size_t len) override {
        if (bytesRead >= limit) {
            return 0;
        }
        size_t remaining = limit - bytesRead;
        size_t read = reader->Read(buf, std::min(len, remaining));
        bytesRead += read;
        return read;
    }
};

class TeeReader : public Reader {
private:
    std::vector<Reader*> readers;
    size_t currentReaderIndex;

public:
    TeeReader(const std::vector<Reader*>& r) : readers(r), currentReaderIndex(0) {
    }

    size_t Read(char* buf, size_t len) override {
        if (currentReaderIndex >= readers.size()) {
            return 0;
        }
        size_t read = readers[currentReaderIndex]->Read(buf, len);
        if (read == 0) {
            currentReaderIndex++;
            if (currentReaderIndex < readers.size()) {
                return Read(buf, len);
            }
        }
        return read;
    }
};

class HexDecodingReader : public Reader {
private:
    Reader* reader;
    bool hasReadOddCharacter;

public:
    HexDecodingReader(Reader* r) : reader(r), hasReadOddCharacter(false) {
    }

    size_t Read(char* buf, size_t len) override {
        if (len == 0) {
            return 0;
        }
        size_t read = 0;
        while (read < len) {
            char input[2];
            size_t bytesRead = reader->Read(input, 2);
            if (bytesRead == 0) {
                break;
            }
            assert(bytesRead == 2);
            if (!IsValidHexCharacter(input[0]) || !IsValidHexCharacter(input[1])) {
                hasReadOddCharacter = true;
                break;
            }
            buf[read] = (HexToDec(input[0]) << 4) | HexToDec(input[1]);
            read++;
        }
        return read;
    }

private:
    bool IsValidHexCharacter(char c) {
        return (c >= '0' && c <= '9') || (c >= 'a' && c <= 'f') || (c >= 'A' && c <= 'F');
    }

    int HexToDec(char c) {
        if (c >= '0' && c <= '9') {
            return c - '0';
        } else if (c >= 'a' && c <= 'f') {
            return c - 'a' + 10;
        } else if (c >= 'A' && c <= 'F') {
            return c - 'A' + 10;
        }
        return 0;
    }
};
