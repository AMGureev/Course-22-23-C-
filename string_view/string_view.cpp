#include "string_view.h"

#include <cstring>

#include "algorithm"

StringView::StringView() : string_(nullptr), size_(0) {
}

StringView::StringView(const char *source) : string_(source), size_(std::strlen(source)) {
}

StringView::StringView(const char *cstyle, size_t length) : string_(cstyle), size_(length) {
}

char StringView::operator[](size_t idx) const {
    if (idx >= size_) {
        throw StringViewOutOfRange();
    }
    return string_[idx];
}

char StringView::At(size_t idx) const {
    if (idx >= size_) {
        throw StringViewOutOfRange();
    }
    return string_[idx];
}

char StringView::Front() const {
    if (size_ == 0) {
        throw StringViewOutOfRange();
    }
    return string_[0];
}

char StringView::Back() const {
    if (size_ == 0) {
        throw StringViewOutOfRange();
    }
    return string_[size_ - 1];
}

size_t StringView::Size() const {
    return size_;
}

size_t StringView::Length() const {
    return size_;
}

const char *StringView::Data() const {
    return string_;
}

bool StringView::Empty() const {
    return size_ == 0;
}

void StringView::Swap(StringView &other) {
    std::swap(string_, other.string_);
    std::swap(size_, other.size_);
}

void StringView::RemovePrefix(size_t prefix_size) {
    if (prefix_size >= size_) {
        string_ += size_;
        size_ = 0;
    } else {
        string_ += prefix_size;
        size_ -= prefix_size;
    }
}

void StringView::RemoveSuffix(size_t suffix_size) {
    if (suffix_size >= size_) {
        size_ = 0;
    } else {
        size_ -= suffix_size;
    }
}

StringView StringView::Substr(size_t pos, size_t count) {
    if (pos >= size_) {
        throw StringViewOutOfRange();
    }
    if (count == -1 || pos + count > size_) {
        count = size_ - pos;
    }
    return StringView(string_ + pos, count);
}