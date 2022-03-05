/**
    Min Steps to Make Piles Equal Height: 
    Alexa is given n piles of equal or unequal heights.
    In one step, Alexa can remove any number of boxes from the
    pile which has the maximum height and try to make it equal
    to the one which is just lower than the maximum height of
    the stack. Determine the minimum number of steps required to
    make all of the piles equal in height.
        
    @file min_steps.cpp
    @author Tamir Cohen
    @version 1.0 05/03/2022 
*/

#include <iostream>
#include <bits/stdc++.h>
using namespace std;

/**
    Return the minimum number of steps required to
    make all of the piles equal in height.
    @param piles piles to stack
    @param size piles size
    @return minimum number of steps required
*/
int minSteps(int piles[], size_t size)
{
    // quick sort, sorted in descending order
    sort(piles, piles + size, greater<int>());

    int highest_pile = piles[0];
    int steps = 0;
    for (int i = 0; i < size; i++)
    {
        // need to restack piles
        if (piles[i] != highest_pile)
        {
            steps += i;
            highest_pile = piles[i];
        }
    }
    return steps;
}

int main()
{
    int piles[]{1, 1, 2, 2, 2, 3, 3, 3, 4, 4};
    cout << "Steps needed: " << minSteps(piles, (sizeof(piles) / sizeof(*piles))) << endl;
}