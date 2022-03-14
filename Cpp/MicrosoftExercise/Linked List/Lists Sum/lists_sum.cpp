/**
    Given the head pointers of two linked lists where each linked list
    represents an integer number (each node is a digit),
    add them and return the resulting linked list.

    @file lists_sum.cpp
    @author Tamir Cohen
    @version 1.0 07/03/2022
*/

/*
https://www.educative.io/m/add-two-integers
Solution Explanation

Runtime Complexity
Linear, O(n)

Runtime complexity is based on the length of the linked lists.

Memory Complexity
Linear, O(n)


Solution Breakdown
For a better understanding of the problem, let’s take a look at an example.
Suppose we want to add the integers 9901 and 237. The result of this addition would be 10138.

The integers are stored inverted in the linked lists to make the addition easier.
Now, the most significant digit of the number is the last element of the linked list.

For the addition, we’ll start from the heads of the two linked lists.
At each iteration, we add the current digits of the two lists and insert a new node
with the resulting digit at the tail of the result linked list.

We’ll also need to maintain carry at each step.
We’ll keep doing this for all digits in both the linked lists.
If one of the linked lists ends sooner, we’ll continue with the other linked list.
Once both of the linked lists are exhausted, and no carry is left to be added, the algorithm will terminate.
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

/**
    Return the number represented by the list (assuming left to right, first is MSB)
    @param linked_list any Node (assuming digit is 0-9, and first is 1-9)
    @return number represented by the list
*/
int list_to_num(const Node *const linked_list)
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

/**
    Generate random value linked list
    @param length wanted list length
    @return new random list, allocated on the heap
*/
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

/**
    Pretty print linked lists
    @param linked_list linked lists of digits
*/
void print_list(const Node *const linked_list)
{
    const Node *head = linked_list;
    string data_line{"|"};
    while (head->next != nullptr)
    {
        data_line += " " + to_string(head->digit) + " |";
        head = head->next;
    }

    cout << std::string(data_line.length(), '-') << endl;
    cout << data_line << endl;
    cout << std::string(data_line.length(), '-') << endl;
}

int main()
{
    srand(time(nullptr));
    Node *list = gen_list(5);
    print_list(list);
    int num = list_to_num(list);
    cout << "First list as number: " << num << endl;

    list = gen_list(3);
    print_list(list);
    int num2 = list_to_num(list);
    cout << "Second list as number: " << num2 << endl;

    cout << "lists as numbers sum: " << num + num2 << endl;
}