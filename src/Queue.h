#pragma once
#include <vector>

class Queue {
private:
    struct Node {
        int data;
        Node* next;
        explicit Node(int value) : data(value), next(nullptr) {}
    };

    Node* front_;
    Node* rear_;
    std::size_t size_;

public:
    Queue() : front_(nullptr), rear_(nullptr), size_(0) {}
    ~Queue() { clear(); }

    Queue(const Queue& other) : front_(nullptr), rear_(nullptr), size_(0) {
        for (int value : other.traverse()) insert(value);
    }

    Queue& operator=(const Queue& other) {
        if (this != &other) {
            clear();
            for (int value : other.traverse()) insert(value);
        }
        return *this;
    }

    Queue(Queue&& other) noexcept
        : front_(other.front_), rear_(other.rear_), size_(other.size_) {
        other.front_ = other.rear_ = nullptr;
        other.size_ = 0;
    }

    Queue& operator=(Queue&& other) noexcept {
        if (this != &other) {
            clear();
            front_ = other.front_;
            rear_ = other.rear_;
            size_ = other.size_;
            other.front_ = other.rear_ = nullptr;
            other.size_ = 0;
        }
        return *this;
    }

    void insert(int value) { // Enqueue
        Node* newNode = new Node(value);
        if (!rear_) {
            front_ = rear_ = newNode;
        } else {
            rear_->next = newNode;
            rear_ = newNode;
        }
        ++size_;
    }

    bool deleteValue(int value) {
        Node* current = front_;
        Node* previous = nullptr;

        while (current) {
            if (current->data == value) {
                if (previous) previous->next = current->next;
                else front_ = current->next;

                if (current == rear_) rear_ = previous;

                delete current;
                --size_;

                if (size_ == 0) front_ = rear_ = nullptr;
                return true;
            }
            previous = current;
            current = current->next;
        }
        return false;
    }

    bool dequeue(int& value) {
        if (!front_) return false;
        Node* node = front_;
        value = node->data;
        front_ = node->next;
        delete node;
        --size_;

        if (!front_) rear_ = nullptr;
        return true;
    }

    bool search(int value) const {
        for (Node* current = front_; current; current = current->next)
            if (current->data == value) return true;
        return false;
    }

    std::vector<int> traverse() const {
        std::vector<int> result;
        result.reserve(size_);
        for (Node* current = front_; current; current = current->next)
            result.push_back(current->data);
        return result;
    }

    void clear() noexcept {
        while (front_) {
            Node* next = front_->next;
            delete front_;
            front_ = next;
        }
        rear_ = nullptr;
        size_ = 0;
    }

    std::size_t size() const { return size_; }
    bool empty() const { return front_ == nullptr; }
};
