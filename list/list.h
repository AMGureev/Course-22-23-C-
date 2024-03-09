#pragma once

#include <cstdint>
#include <optional>

template <typename T>
class List {
public:
    class ListNode {
    public:
        ListNode() : next_(nullptr), prev_(nullptr) {
        }

        ListNode(const T& value, ListNode* next, ListNode* prev) : value_(std::move(value)), next_(next), prev_(prev) {
        }

        ListNode(T&& value, ListNode* next, ListNode* prev) : value_(std::move(value)), next_(next), prev_(prev) {
        }

        ~ListNode() {
        }

        T& operator*() {
            return value_.value();
        }

        ListNode*& Prev() {
            return prev_;
        }

        ListNode*& Next() {
            return next_;
        }

    private:
        std::optional<T> value_;
        ListNode* next_;
        ListNode* prev_;
    };

    class Iterator {
    public:
        Iterator() : curr_(nullptr), position_(0) {
        }

        explicit Iterator(ListNode* curr, size_t position, size_t list_size)
            : curr_(curr), position_(position), list_size_(list_size) {
        }

        Iterator& operator--() {
            if (position_ != list_size_) {
                curr_ = curr_->Prev();
            }
            --position_;
            return *this;
        }

        Iterator operator--(int) {
            Iterator tmp = *this;
            if (position_ != list_size_) {
                curr_ = curr_->Prev();
            }
            --position_;
            return tmp;
        }

        T& operator*() {
            return *(*curr_);
        }

        T* operator->() const {
            return &(*(*curr_));
        }

        bool operator==(const Iterator& rhs) const {
            return position_ == rhs.position_;
        }

        bool operator!=(const Iterator& rhs) const {
            return position_ != rhs.position_;
        }
        Iterator& operator++() {
            if (position_ < list_size_ - 1) {
                curr_ = curr_->Next();
            }
            ++position_;
            return *this;
        }

        Iterator operator++(int) {
            Iterator tmp = *this;
            if (position_ < list_size_ - 1) {
                curr_ = curr_->Next();
            }
            ++position_;
            return tmp;
        }

    private:
        ListNode* curr_;
        size_t position_;
        size_t list_size_;
    };

    Iterator Begin() const {
        if (start_node_ == nullptr) {
            return End();
        }
        return Iterator(start_node_, 0, size_);
    }

    Iterator End() const {
        return Iterator(end_node_, size_, size_);
    }

    T& Front() {
        return *(*start_node_);
    }

    const T& Front() const {
        return *(*start_node_);
    }

    T& Back() {
        return *(*(end_node_));
    }

    T& Back() const {
        return *(*(end_node_));
    }

    void PopBack() {
        Unlink(end_node_);
    }

    void PopFront() {
        Unlink(start_node_);
    }

    List() {
        size_ = 0;
        start_node_ = nullptr;
        end_node_ = nullptr;
    }

    List(const List& other) {
        size_ = 0;
        start_node_ = nullptr;
        end_node_ = nullptr;

        for (Iterator iter = other.Begin(); iter != other.End(); ++iter) {
            PushBack(*iter);
        }
    }

    List(List&& other) {
        size_ = other.Size();
        start_node_ = other.start_node_;
        end_node_ = other.end_node_;
        other.size_ = 0;
        other.start_node_ = nullptr;
        other.end_node_ = nullptr;
    }

    ~List() {
        Clear();
    }

    void Clear() {
        ListNode* curr = start_node_;
        if (curr == nullptr) {
            return;
        }
        while (curr != nullptr) {
            ListNode* tmp = curr->Next();
            delete curr;
            curr = tmp;
        }
        size_ = 0;
    }

    List& operator=(const List& other) {
        Clear();
        size_ = 0;
        if (other.size_ == 0) {
            start_node_ = nullptr;
            end_node_ = nullptr;
        } else {
            for (Iterator iter = other.Begin(); iter != other.End(); ++iter) {
                PushBack(*iter);
            }
        }
        return *this;
    }

    List& operator=(List&& other) noexcept {
        if (this == &other) {
            return *this;
        }

        Clear();
        size_ = other.Size();
        start_node_ = other.start_node_;
        end_node_ = other.end_node_;
        other.size_ = 0;
        other.start_node_ = nullptr;
        other.end_node_ = nullptr;
        return *this;
    }

    bool IsEmpty() const {
        return size_ == 0;
    }

    size_t Size() const {
        return size_;
    }

    void PushBack(T& elem) {
        if (size_ == 0) {
            ListNode* node = new ListNode(elem, nullptr, nullptr);
            start_node_ = node;
            end_node_ = start_node_;
            ++size_;
        } else {
            ++size_;
            ListNode* node = new ListNode(elem, nullptr, end_node_);
            end_node_->Next() = node;
            end_node_ = node;
        }
    }

    void PushBack(T&& elem) {
        if (size_ == 0) {
            ListNode* node = new ListNode(std::move(elem), nullptr, nullptr);
            start_node_ = node;
            end_node_ = start_node_;
            ++size_;
        } else {
            ++size_;
            ListNode* node = new ListNode(std::move(elem), nullptr, end_node_);
            end_node_->Next() = node;
            end_node_ = node;
        }
    }

    void PushFront(const T& elem) {
        if (size_ == 0) {
            delete start_node_;
            ListNode* node = new ListNode(elem, nullptr, nullptr);
            start_node_ = node;
            end_node_ = start_node_;
            ++size_;
        } else {
            ++size_;
            ListNode* node = new ListNode(elem, start_node_, nullptr);
            start_node_->Prev() = node;
            start_node_ = node;
        }
    }

    void PushFront(T&& elem) {
        if (size_ == 0) {
            delete start_node_;
            ListNode* node = new ListNode(std::move(elem), nullptr, nullptr);
            start_node_ = node;
            end_node_ = start_node_;
            ++size_;
        } else {
            ++size_;
            ListNode* node = new ListNode(std::move(elem), start_node_, nullptr);
            start_node_->Prev() = node;
            start_node_ = node;
        }
    }

    void Unlink(ListNode* node) {
        ListNode* tmp_next = node->Next();
        ListNode* tmp_prev = node->Prev();

        if (tmp_next != nullptr) {
            tmp_next->Prev() = tmp_prev;
        }

        if (tmp_prev != nullptr) {
            tmp_prev->Next() = tmp_next;
        } else {
            start_node_ = tmp_next;
        }

        if (node == start_node_) {
            start_node_ = tmp_next;
        }

        if (node == end_node_) {
            end_node_ = tmp_prev;
        }

        delete node;
        --size_;

        if (size_ == 0) {
            start_node_ = nullptr;
            end_node_ = nullptr;
        }
    }

private:
    size_t size_;
    ListNode* start_node_;
    ListNode* end_node_;
};

template <typename T>
typename List<T>::Iterator begin(List<T>& list) {  // NOLINT
    return list.Begin();
}

template <typename T>
typename List<T>::Iterator end(List<T>& list) {  // NOLINT
    return list.End();
}