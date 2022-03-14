/**
    Given the root of a binary tree, display the node values at each level.

    @file level_order.cpp
    @author Tamir Cohen
    @version 1.0 13/03/2022
*/

/*
https://www.educative.io/m/level-order-traversal-binary-tree

Solution Explanation

Runtime Complexity
The runtime complexity of this solution is linear, O(n).

Memory Complexity
The memory complexity of this solution is linear, O(n).


Solution Breakdown
Here, you are using two queues: current_queue and next_queue.
You push the nodes in both queues alternately based on the current level number.

You’ll dequeue nodes from the current_queue, print the node’s data,
and enqueue the node’s children to the next_queue.

Once the current_queue becomes empty, you have processed all nodes for the current level_number.
To indicate the new level, print a line break (’\n’), swap the two queues, and continue with the above-mentioned logic.

After printing the leaf nodes from the current_queue, swap current_queue and next_queue.
Since the current_queue would be empty, you can terminate the loop.
*/

#include <iostream>
#include <queue>
using namespace std;

// A Binary Tree Node
struct Node
{
    int data;
    struct Node *left, *right;

    Node(int data) : data{data}, left{nullptr}, right{nullptr} {};

    void PrintLevelOrder() const;
};

void Node::PrintLevelOrder() const
{
    queue<const Node *> current_queue; // current level nodes
    queue<const Node *> next_queue;    // next level nodes

    current_queue.push(this);

    while (!current_queue.empty())
    {
        const Node *temp = current_queue.front();
        current_queue.pop();
        cout << temp->data << (current_queue.empty() ? "" : ", "); // print my self

        // next node is my left son
        if (temp->left != nullptr)
        {
            next_queue.push(temp->left);
        }

        // than my right son
        if (temp->right != nullptr)
        {
            next_queue.push(temp->right);
        }

        // if i'm done with my level i go to the next one
        if (current_queue.empty())
        {
            cout << endl;
            current_queue = move(next_queue); // move assignment o(1)
            next_queue = queue<const Node *>();
        }
    }
}

// int main()
// {
//     cout << "Running!" << endl;
//     Node *root = new Node(1);
//     root->left = new Node(2);
//     root->right = new Node(3);
//     root->left->left = new Node(4);
//     root->left->right = new Node(5);
//     root->left->right->right = new Node(12);
//     root->PrintLevelOrder();
// }
