// Gtest.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "gtest/gtest.h"

TEST(SquareRootTest, PositiveNos)
{
    EXPECT_EQ(18.0, square‑root(324.0));
    EXPECT_EQ(25.4, square‑root(645.16));
    EXPECT_EQ(50.3321, square‑root(2533.310224));
}

TEST(SquareRootTest, ZeroAndNegativeNos)
{
    ASSERT_EQ(0.0, square‑root(0.0));
    ASSERT_EQ(‑1, square‑root(‑22.0));
}

class Tmath
{
public:
    int add(int x, int y) { return x + y; }
    int multiply(int x, int y) { return x * y; }
};

int main()
{
    std::cout << "Hello World!\n";
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started:
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
