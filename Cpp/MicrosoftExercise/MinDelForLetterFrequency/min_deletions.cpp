/**
    Minimum Deletions to Make Character Frequencies Unique:
    A string s is called good if there are no two different
    characters in s that have the same frequency.
    Given a string s, returns the minimum number of characters
    needed to delete to make s good.

    Constrains:
        * 1 <= s.length <= 10^5
        * s contains only lowercase English letters.

    @file min_deletions.cpp
    @author Tamir Cohen
    @version 1.0 05/03/2022
*/

#include <iostream>
#include <string>
#include <bits/stdc++.h>
using namespace std;

// 'a' is the first ascii char of lowercase English letters
const unsigned short INDEX_SHIFT{'a'};
const unsigned short NUM_OF_EN_LETTERS{26};

void debug(unsigned long int arr[NUM_OF_EN_LETTERS])
{
    for (int i = 0; i < NUM_OF_EN_LETTERS; i++)
    {
        cout << "'" << (char)(i + INDEX_SHIFT) << "': " << arr[i] << endl;
    }
}

/**
    Return the minimum number of characters you need to delete to make s good.
    @param s any string (under given constrains)
    @return minimum number of characters you need to delete
*/
int minDeletions(string s)
{
    unsigned long int frequency[NUM_OF_EN_LETTERS]{0};

    // looping through the characters of s, counting frequency
    for (char &c : s)
        frequency[c - INDEX_SHIFT] += 1;

    // quick sort algorithm on const size array ~ O(1)
    sort(frequency, frequency + NUM_OF_EN_LETTERS, greater<int>());

    int deletions{0};

    for (size_t i = 1; i < NUM_OF_EN_LETTERS; i++)
    {
        // the array is sorted in descending order, so if we at 0 we are done
        if (frequency[i] == 0)
        {
            break;
        }

        // check if frequency needs to be reduced
        if (frequency[i] >= frequency[i - 1])
        {
            // frequency to 0
            if (frequency[i - 1] == 0)
            {
                deletions += frequency[i];
                frequency[i] = 0;
            }
            // frequency to lowast - 1
            else
            {
                deletions += frequency[i] - (frequency[i - 1] - 1);
                frequency[i] = frequency[i - 1] - 1;
            }
        }
    }
    return deletions;
}

int main()
{
    string s = "aab";
    int del = minDeletions(s);

    if (del == 0)
    {
        cout << "s is already good." << endl;
    }
    else
    {
        cout << "You need to make " << del << " deletions" << endl;
    }

    s = "aaabbbcc";
    del = minDeletions(s);

    if (del == 0)
    {
        cout << "s is already good." << endl;
    }
    else
    {
        cout << "You need to make " << del << " deletions" << endl;
    }

    s = "ceabaacb";
    del = minDeletions(s);

    if (del == 0)
    {
        cout << "s is already good." << endl;
    }
    else
    {
        cout << "You need to make " << del << " deletions" << endl;
    }
}