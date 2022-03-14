/**
    You are given a linked list where the node has two pointers.
    The first is the regular ‘next’ pointer.
    The second pointer is called ‘arbitrary_pointer’ and
    it can point to any node in the linked list.

    Your job is to write code to make a deep copy of the given linked list.
    Here, deep copy means that any operations on the original list
    (inserting, modifying and removing) should not affect the copied list.

    @file arbitrary_pointer.cpp
    @author Tamir Cohen
    @version 1.0 08/03/2022
*/

/*
https://www.educative.io/m/copy-linked-list-with-arbitrary-pointer

Solution Explanation

Runtime Complexity
Linear, O(n).

Memory Complexity
Linear, O(n).

Solution Breakdown
This approach uses a map to track arbitrary nodes pointed by the original list.
You will create a deep copy of the original linked list (say list_orig) in two passes.

In the first pass, create a copy of the original linked list. While creating this copy,
use the same values for data and arbitrary_pointer in the new list.
Also, keep updating the map with entries where the key is the address to the old node
and the value is the address of the new node.
Once the copy has been created, do another pass on the copied linked list and update
arbitrary pointers to the new address using the map created in the first pass.
*/

#include <cstdlib> // required for rand()
#include <ctime>   // required for time( )
#include <iostream>
#include <unordered_map>

using namespace std;

class Node
{
public:
    int data{0};
    Node *next{nullptr};
    Node *arbitrary{nullptr};

    Node(int data = 0) : data{data}, next{nullptr}, arbitrary{nullptr} {};

    // Copy constructor
    Node *deep_copy(const Node *source);
};

Node *Node::deep_copy(const Node *source)
{
    if (source == nullptr)
    {
        return nullptr;
    }

    const Node *current = source; // allocating new node on the heap
    Node *new_head = nullptr;
    Node *new_prev = nullptr;
    unordered_map<const Node *, Node *> umap;

    // create copy of the linked list, recording the corresponding
    // nodes in hashmap without updating arbitrary pointer
    while (current != nullptr)
    {
        Node *new_node = new Node{current->data};

        // copy the old arbitrary pointer in the new node
        new_node->arbitrary = current->arbitrary;

        // link the previous node to the new one
        if (new_prev != nullptr)
        {
            new_prev->next = new_node;
        }
        else
        { // im the first new node
            new_head = new_node;
        }

        // map the old entries to the new ones
        umap[current] = new_node;

        // move to the next node
        new_prev = new_node;
        current = current->next;
    }

    Node *new_current = new_head;
    umap[nullptr] = nullptr; // for cases where the node has nullptr as arbitrary pointer

    // updating arbitrary_pointer
    while (new_current != nullptr)
    {
        new_current->arbitrary = umap[new_current->arbitrary];
        new_current = new_current->next;
    }

    return new_head;
}

int main()
{
}