#pragma once
#include <vector>

class Stack {
private:
    struct Node {
        int data;
        Node* next;
        explicit Node(int value) : data(value), next(nullptr) {}
    };

    Node* top_;
    std::size_t size_;

public:
    Stack() : top_(nullptr), size_(0) {}
    ~Stack() { clear(); }

    Stack(const Stack& other) : top_(nullptr), size_(0) {
        // Rebuild in original stack order.
        std::vector<int> values = other.traverse();
        for (auto it = values.rbegin(); it != values.rend(); ++it) insert(*it);
    }

    Stack& operator=(const Stack& other) {
        if (this != &other) {
            clear();
            std::vector<int> values = other.traverse();
            for (auto it = values.rbegin(); it != values.rend(); ++it) insert(*it);
        }
        return *this;
    }

    Stack(Stack&& other) noexcept : top_(other.top_), size_(other.size_) {
        other.top_ = nullptr;
        other.size_ = 0;
    }

    Stack& operator=(Stack&& other) noexcept {
        if (this != &other) {
            clear();
            top_ = other.top_;
            size_ = other.size_;
            other.top_ = nullptr;
            other.size_ = 0;
        }
        return *this;
    }

    void insert(int value) { // Push
        Node* newNode = new Node(value);
        newNode->next = top_;
        top_ = newNode;
        ++size_;
    }

    bool deleteValue(int value) {
        Node* current = top_;
        Node* previous = nullptr;

        while (current) {
            if (current->data == value) {
                if (previous) previous->next = current->next;
                else top_ = current->next;
                delete current;
                --size_;
                return true;
            }
            previous = current;
            current = current->next;
        }
        return false;
    }

    bool pop(int& value) {
        if (!top_) return false;
        Node* node = top_;
        value = node->data;
        top_ = node->next;
        delete node;
        --size_;
        return true;
    }

    bool search(int value) const {
        for (Node* current = top_; current; current = current->next)
            if (current->data == value) return true;
        return false;
    }

    std::vector<int> traverse() const {
        std::vector<int> result;
        result.reserve(size_);
        for (Node* current = top_; current; current = current->next)
            result.push_back(current->data);
        return result;
    }

    void clear() noexcept {
        while (top_) {
            Node* next = top_->next;
            delete top_;
            top_ = next;
        }
        size_ = 0;
    }

    std::size_t size() const { return size_; }
    bool empty() const { return top_ == nullptr; }
};
