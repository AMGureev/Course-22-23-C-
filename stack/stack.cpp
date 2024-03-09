#include "stack.h"

Node::Node(int32_t value, Node* previous) : value(value), previous(previous) {
}

Stack::Stack() : head_(nullptr), size_(0) {
}

Stack::~Stack() {
    Clear();
}

void Stack::Push(int32_t value) {
    Node* new_node = new Node(value, head_);
    head_ = new_node;
    size_++;
}

void Stack::Pop() {
    if (!Empty()) {
        Node* old_head = head_;
        head_ = head_->previous;
        delete old_head;
        size_--;
    }
}

int32_t Stack::Top() const {
    if (!Empty()) {
        return head_->value;
    }
    return 0;
}

int32_t Stack::Size() const {
    return size_;
}

void Stack::Clear() {
    while (!Empty()) {
        Pop();
    }
}

bool Stack::Empty() const {
    return size_ == 0;
}