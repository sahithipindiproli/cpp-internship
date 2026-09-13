# Core Data Structures From Scratch

A C++ implementation of four fundamental data structures built manually with dynamic memory:

- Singly Linked List
- Doubly Linked List
- Stack
- Queue

The project includes a test suite and explicit memory-management logic to prevent memory leaks.

## Features

Every structure provides:

- Insert
- Delete
- Search
- Traversal
- Empty/size checks
- Destructor-based cleanup

Stack additionally provides `pop()` and Queue provides `dequeue()`.

The linked lists, stack, and queue do not use STL containers as their underlying storage. `std::vector` is used only to expose traversal results to the test suite.

## Project Structure

```text
DataStructures/
├── src/
│   ├── SinglyLinkedList.h
│   ├── DoublyLinkedList.h
│   ├── Stack.h
│   └── Queue.h
├── tests/
│   └── test_main.cpp
├── README.md
└── .gitignore
```

## Compilation

### Windows / MinGW

From the project root:

```bash
g++ -std=c++17 -Wall -Wextra -pedantic tests/test_main.cpp -o tests.exe
```

Run:

```bash
tests.exe
```

### Linux / macOS

```bash
g++ -std=c++17 -Wall -Wextra -pedantic tests/test_main.cpp -o tests
./tests
```

## Expected Test Result

```text
[PASS] Singly Linked List - insert/delete/search/traversal
[PASS] Doubly Linked List - insert/delete/search/traversal
[PASS] Stack - insert/delete/search/traversal
[PASS] Queue - insert/delete/search/traversal
[PASS] Copy/Move and memory ownership

Tests passed: 5
Tests failed: 0
```

## Complexity Analysis

Let `n` be the number of elements.

| Structure | Insert | Delete by value | Search | Traversal | Space |
|---|---:|---:|---:|---:|---:|
| Singly Linked List | O(1)* | O(n) | O(n) | O(n) | O(n) |
| Doubly Linked List | O(1)* | O(n) | O(n) | O(n) | O(n) |
| Stack | O(1) | O(n)** | O(n) | O(n) | O(n) |
| Queue | O(1) | O(n) | O(n) | O(n) | O(n) |

`*` Insert is at the end and uses a tail pointer.

`**` `deleteValue()` searches for an arbitrary value. Normal stack `pop()` is O(1).

Queue `dequeue()` is O(1).

## Memory Management

Each node is allocated using `new` and released using `delete`.

Each class has a `clear()` function and destructor that release every dynamically allocated node.

The classes also implement copy constructors, copy assignment, move constructors, and move assignment operators so that ownership is handled safely when objects are copied or moved.

No raw allocated node is intentionally left without an owner.

For additional leak checking on Linux, the test executable can be run with tools such as Valgrind when installed:

```bash
valgrind --leak-check=full ./tests
```

## Design Notes

### Singly Linked List
Maintains `head` and `tail` pointers. Each node points to the next node.

### Doubly Linked List
Maintains `head` and `tail`. Each node has both `prev` and `next` pointers, allowing forward and reverse traversal.

### Stack
Implemented using linked nodes. The top is stored in `top_`, so insertion/push and pop are O(1).

### Queue
Implemented using linked nodes with both `front_` and `rear_` pointers. Enqueue and dequeue are O(1).

## Author

C++ Programming Internship Project - YR NOVATECH
