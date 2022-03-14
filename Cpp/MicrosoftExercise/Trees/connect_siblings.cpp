/**
    Connect the sibling pointer to the next node in the same level.
    The last node in each level should point to the first node of the next level in the tree.

    @file connect_sibling.cpp
    @author Tamir Cohen
    @version 1.0 05/03/2022
*/

/*
https://www.educative.io/m/connect-all-siblings

Solution Explanation

Runtime Complexity
Linear, O(n).

Memory Complexity
Constant O(1).


Solution Breakdown
A binary tree is a data structure made up of nodes, where each node contains
a “left” reference, a “right” reference, and a data element.
The topmost node in the tree is called the root. Every node except the ‘root’ node is connected
by a directed edge from exactly one other node. This node is called the parent of that node.
On the other hand, each node can be connected to an arbitrary number of nodes, called children.
Nodes with the same parent node are called siblings.

Each node in the above binary tree has one more pointer i.e. next along
with the left and right pointers. ‘Next’ is used to connect one node to the other.
After connecting siblings, a linked-list-like structure is formed whose head
is the root node. We keep two pointers current and last.
‘current’ is the node we are working at and ‘last’ is the last node in the
linked list already constructed (i.e. siblings already connected).

~~ Below are the steps we use to connect all siblings in the tree:
Initially set both current and last as 'root'
while current node is not null
  If current node has a left child, append this left node to the last and make it last node.
  If current node has a right child, append this right node to the last and make it last node.
  update current node to current's next node
*/

#include <iostream>
#include <queue>
#include <list>
using namespace std;

// A Binary Tree Node
struct Node
{
    int data;
    struct Node *left, *right;

    Node(int data) : data{data}, left{nullptr}, right{nullptr} {};

    void ConnectSiblings();
};

void Node::ConnectSiblings()
{
    queue<Node *> current_queue; // current level nodes
    queue<Node *> next_queue;    // next level nodes
    list<Node *> tree_list;      // tree nodes as list

    current_queue.push(this);

    while (!current_queue.empty())
    {
        Node *temp = current_queue.front();
        tree_list.push_back(temp);
        current_queue.pop();

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
            current_queue = move(next_queue); // move assignment o(1)
            next_queue = queue<Node *>();
        }
    }

    while (!tree_list.empty())
    {
        Node *temp = tree_list.front();

        if (!tree_list.empty())
        {
            temp->left = temp->right = tree_list.front();
        }
        else
        {
            temp->left = temp->right = nullptr;
        }
    }
}

int main()
{
    cout << "Running!" << endl;
    Node *root = new Node(1);
    root->left = new Node(2);
    root->right = new Node(3);
    root->left->left = new Node(4);
    root->left->right = new Node(5);
    root->left->right->right = new Node(12);
    root->ConnectSiblings();
}
