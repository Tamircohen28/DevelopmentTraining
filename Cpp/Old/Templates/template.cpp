// template.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "template.h";
using namespace templates;

void templates::print_cell(int address)
{
    std::cout << "Address: " << address << " Data: " << reinterpret_cast<const int *>(address) << std::endl;
}

int main()
{
    // inital message location
    uint8_t *m_ptr = nullptr;

    std::cout << "Starting address of ptr: " << int(m_ptr) << std::endl;

    // variables to messgage
    int abc = 10;                                 // 4 bytes
    int a[] = {1, 3, 3};                          // 12 bytes
    char b[] = {"I hate memory allocations :-)"}; // 15 bytes
    struct s_arr<int> int_arr =
    {
        a, 12
    };
    struct s_arr<char> char_arr =
    {
        b, sizeof(b)
    };

    size_t m_size = size(m_ptr, 0, 'c', 1, abc, 8, int_arr, char_arr);

    std::cout << "Message size is " << m_size << " bytes" << std::endl;
    std::cout << "End address of ptr: " << int(m_ptr) << std::endl;

    // printing message in memory
    std::cout << "\nMessage Cells:" << std::endl;
    for (size_t i = 0; i < m_size; i++)
    {
        if (isprint(*(m_ptr + i)))
        {
            std::cout << "[" << i << "]: " << (char)*(m_ptr + i) << std::endl;
        }
        else
        {
            std::cout << "[" << i << "]: " << (int)*(m_ptr + i) << std::endl;
        }
    }
}