#include <iostream>
#include <string>
#include <vector>
#include <stdexcept>

#include "../src/SinglyLinkedList.h"
#include "../src/DoublyLinkedList.h"
#include "../src/Stack.h"
#include "../src/Queue.h"

static int testsPassed = 0;
static int testsFailed = 0;

#define EXPECT_TRUE(condition) \
    do { if (!(condition)) throw std::runtime_error("Expected true: " #condition); } while (0)

#define EXPECT_FALSE(condition) \
    do { if ((condition)) throw std::runtime_error("Expected false: " #condition); } while (0)

#define EXPECT_EQ(actual, expected) \
    do { if (!((actual) == (expected))) throw std::runtime_error("Values are not equal: " #actual " and " #expected); } while (0)

template <typename Test>
void runTest(const std::string& name, Test test) {
    try {
        test();
        ++testsPassed;
        std::cout << "[PASS] " << name << '\n';
    } catch (const std::exception& e) {
        ++testsFailed;
        std::cout << "[FAIL] " << name << " -> " << e.what() << '\n';
    }
}

void testSinglyLinkedList() {
    SinglyLinkedList list;
    EXPECT_TRUE(list.empty());

    list.insert(10);
    list.insert(20);
    list.insert(30);

    EXPECT_EQ(list.traverse(), std::vector<int>({10, 20, 30}));
    EXPECT_TRUE(list.search(20));
    EXPECT_FALSE(list.search(99));

    EXPECT_TRUE(list.deleteValue(20));
    EXPECT_EQ(list.traverse(), std::vector<int>({10, 30}));
    EXPECT_FALSE(list.deleteValue(99));
    EXPECT_EQ(list.size(), static_cast<std::size_t>(2));
}

void testDoublyLinkedList() {
    DoublyLinkedList list;
    list.insert(10);
    list.insert(20);
    list.insert(30);

    EXPECT_EQ(list.traverse(), std::vector<int>({10, 20, 30}));
    EXPECT_EQ(list.reverseTraverse(), std::vector<int>({30, 20, 10}));
    EXPECT_TRUE(list.search(10));

    EXPECT_TRUE(list.deleteValue(10));
    EXPECT_TRUE(list.deleteValue(30));
    EXPECT_EQ(list.traverse(), std::vector<int>({20}));
    EXPECT_EQ(list.reverseTraverse(), std::vector<int>({20}));
}

void testStack() {
    Stack stack;
    int value = 0;

    stack.insert(10);
    stack.insert(20);
    stack.insert(30);

    EXPECT_EQ(stack.traverse(), std::vector<int>({30, 20, 10}));
    EXPECT_TRUE(stack.search(20));
    EXPECT_FALSE(stack.search(99));

    EXPECT_TRUE(stack.pop(value));
    EXPECT_EQ(value, 30);

    EXPECT_TRUE(stack.deleteValue(10));
    EXPECT_EQ(stack.traverse(), std::vector<int>({20}));
    EXPECT_FALSE(stack.deleteValue(99));
}

void testQueue() {
    Queue queue;
    int value = 0;

    queue.insert(10);
    queue.insert(20);
    queue.insert(30);

    EXPECT_EQ(queue.traverse(), std::vector<int>({10, 20, 30}));
    EXPECT_TRUE(queue.search(20));
    EXPECT_FALSE(queue.search(99));

    EXPECT_TRUE(queue.dequeue(value));
    EXPECT_EQ(value, 10);

    EXPECT_TRUE(queue.deleteValue(30));
    EXPECT_EQ(queue.traverse(), std::vector<int>({20}));
    EXPECT_FALSE(queue.deleteValue(99));
}

void testCopyAndMove() {
    SinglyLinkedList original;
    original.insert(1);
    original.insert(2);

    SinglyLinkedList copy(original);
    EXPECT_EQ(copy.traverse(), std::vector<int>({1, 2}));

    SinglyLinkedList moved(std::move(copy));
    EXPECT_EQ(moved.traverse(), std::vector<int>({1, 2}));
    EXPECT_TRUE(copy.empty());

    Queue queue;
    queue.insert(5);
    Queue queueCopy = queue;
    EXPECT_EQ(queueCopy.traverse(), std::vector<int>({5}));
}

int main() {
    runTest("Singly Linked List - insert/delete/search/traversal", testSinglyLinkedList);
    runTest("Doubly Linked List - insert/delete/search/traversal", testDoublyLinkedList);
    runTest("Stack - insert/delete/search/traversal", testStack);
    runTest("Queue - insert/delete/search/traversal", testQueue);
    runTest("Copy/Move and memory ownership", testCopyAndMove);

    std::cout << "\nTests passed: " << testsPassed
              << "\nTests failed: " << testsFailed << '\n';

    return testsFailed == 0 ? 0 : 1;
}
