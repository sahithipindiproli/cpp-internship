#pragma once
#include <vector>

class DoublyLinkedList {
private:
    struct Node {
        int data;
        Node* prev;
        Node* next;
        explicit Node(int value) : data(value), prev(nullptr), next(nullptr) {}
    };

    Node* head;
    Node* tail;
    std::size_t size_;

public:
    DoublyLinkedList() : head(nullptr), tail(nullptr), size_(0) {}
    ~DoublyLinkedList() { clear(); }

    DoublyLinkedList(const DoublyLinkedList& other)
        : head(nullptr), tail(nullptr), size_(0) {
        for (int value : other.traverse()) insert(value);
    }

    DoublyLinkedList& operator=(const DoublyLinkedList& other) {
        if (this != &other) {
            clear();
            for (int value : other.traverse()) insert(value);
        }
        return *this;
    }

    DoublyLinkedList(DoublyLinkedList&& other) noexcept
        : head(other.head), tail(other.tail), size_(other.size_) {
        other.head = other.tail = nullptr;
        other.size_ = 0;
    }

    DoublyLinkedList& operator=(DoublyLinkedList&& other) noexcept {
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
        if (!tail) {
            head = tail = newNode;
        } else {
            newNode->prev = tail;
            tail->next = newNode;
            tail = newNode;
        }
        ++size_;
    }

    bool deleteValue(int value) {
        Node* current = head;

        while (current) {
            if (current->data == value) {
                if (current->prev) current->prev->next = current->next;
                else head = current->next;

                if (current->next) current->next->prev = current->prev;
                else tail = current->prev;

                delete current;
                --size_;

                if (size_ == 0) head = tail = nullptr;
                return true;
            }
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

    std::vector<int> reverseTraverse() const {
        std::vector<int> result;
        result.reserve(size_);
        for (Node* current = tail; current; current = current->prev)
            result.push_back(current->data);
        return result;
    }

    void clear() noexcept {
        while (head) {
            Node* next = head->next;
            delete head;
            head = next;
        }
        head = tail = nullptr;
        size_ = 0;
    }

    std::size_t size() const { return size_; }
    bool empty() const { return head == nullptr; }
};
