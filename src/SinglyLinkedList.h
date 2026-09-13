#pragma once
#include <vector>

class SinglyLinkedList {
private:
    struct Node {
        int data;
        Node* next;
        explicit Node(int value) : data(value), next(nullptr) {}
    };

    Node* head;
    Node* tail;
    std::size_t size_;

public:
    SinglyLinkedList() : head(nullptr), tail(nullptr), size_(0) {}

    ~SinglyLinkedList() { clear(); }

    SinglyLinkedList(const SinglyLinkedList& other)
        : head(nullptr), tail(nullptr), size_(0) {
        for (int value : other.traverse()) insert(value);
    }

    SinglyLinkedList& operator=(const SinglyLinkedList& other) {
        if (this != &other) {
            clear();
            for (int value : other.traverse()) insert(value);
        }
        return *this;
    }

    SinglyLinkedList(SinglyLinkedList&& other) noexcept
        : head(other.head), tail(other.tail), size_(other.size_) {
        other.head = other.tail = nullptr;
        other.size_ = 0;
    }

    SinglyLinkedList& operator=(SinglyLinkedList&& other) noexcept {
        if (this != &other) {
            clear();
            head = other.head;
            tail = other.tail;
            size_ = other.size_;
            other.head = other.tail = nullptr;
            other.size_ = 0;
        }
        return *this;
    }

    void insert(int value) {
        Node* newNode = new Node(value);
        if (!head) {
            head = tail = newNode;
        } else {
            tail->next = newNode;
            tail = newNode;
        }
        ++size_;
    }

    bool deleteValue(int value) {
        Node* current = head;
        Node* previous = nullptr;

        while (current) {
            if (current->data == value) {
                if (previous) previous->next = current->next;
                else head = current->next;

                if (current == tail) tail = previous;

                delete current;
                --size_;

                if (size_ == 0) tail = nullptr;
                return true;
            }
            previous = current;
            current = current->next;
        }
        return false;
    }

    bool search(int value) const {
        for (Node* current = head; current; current = current->next)
            if (current->data == value) return true;
        return false;
    }

    std::vector<int> traverse() const {
        std::vector<int> result;
        result.reserve(size_);
        for (Node* current = head; current; current = current->next)
            result.push_back(current->data);
        return result;
    }

    void clear() noexcept {
        while (head) {
            Node* next = head->next;
            delete head;
            head = next;
        }
        tail = nullptr;
        size_ = 0;
    }

    std::size_t size() const { return size_; }
    bool empty() const { return head == nullptr; }
};
