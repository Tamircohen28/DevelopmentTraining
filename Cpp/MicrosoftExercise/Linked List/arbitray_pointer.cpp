// /**
//     You are given a linked list where the node has two pointers.
//     The first is the regular ‘next’ pointer.
//     The second pointer is called ‘arbitrary_pointer’ and
//     it can point to any node in the linked list.

//     Your job is to write code to make a deep copy of the given linked list.
//     Here, deep copy means that any operations on the original list
//     (inserting, modifying and removing) should not affect the copied list.

//     @file arbitrary_pointer.cpp
//     @author Tamir Cohen
//     @version 1.0 08/03/2022
// */

// #include <cstdlib> // required for rand()
// #include <ctime>   // required for time( )
// #include <iostream>
// #include <unordered_map>

// using namespace std;

// class Node
// {
// public:
//     int data{0};
//     Node *next{nullptr};
//     Node *arbitrary{nullptr};

//     Node() : data{0}, next{nullptr}, arbitrary{nullptr} {};

//     // Copy constructor
//     Node *deep_copy(const Node *source);
// };

// Node *Node::deep_copy(const Node *source)
// {
//     const Node *dst = source; // alocating new node on the heap
//     Node *new_head = nullptr;

//     unordered_map<Node *, Node *> umap;

//     while (source.next)
//     {
//         /* code */
//     }

//     return dst;
// }

// int main()
// {
// }