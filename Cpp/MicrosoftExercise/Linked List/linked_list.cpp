/**
    Given the head pointers of two linked lists where each linked list
    represents an integer number (each node is a digit),
    add them and return the resulting linked list.

    @file linked_list.cpp
    @author Tamir Cohen
    @version 1.0 07/03/2022
*/

#include <cstdlib> // required for rand()
#include <ctime>   // required for time( )
#include <iostream>

using namespace std;

class Node
{
public:
    int digit{0}; // assumed this is 0 - 9
    Node *next{nullptr};
};

int list_sum(const Node *const linked_list)
{
    long long int sum{0};
    const Node *head = linked_list;
    while (head->next != nullptr)
    {
        sum *= 10;
        sum += head->digit;
        head = head->next;
    }
    return sum;
}

Node *gen_list(size_t length = 10)
{
    Node *list = new Node; // new node on heap
    Node *head = list;
    Node *node;

    while (length > 0)
    {
        head->digit = rand() % 9 + 1;

        // Link new node with the head
        node = new Node;
        head->next = node;
        head = node;
        length--;
    }

    return list;
}

int main()
{
    srand(time(nullptr));
    Node *list = gen_list(3);
    int sum = list_sum(list);

    int counter = 0;
    while (list->next != nullptr)
    {
        cout << counter << ": " << list->digit << endl;
        list = list->next;
    }
    cout << "list number: " << sum << endl;

    Node *list2 = gen_list(3);
    int sum2 = list_sum(list2);

    counter = 0;
    while (list2->next != nullptr)
    {
        cout << counter << ": " << list2->digit << endl;
        list2 = list2->next;
    }
    cout << "list2 number: " << sum2 << endl;

    cout << "lists sum: " << sum + sum2 << endl;
}