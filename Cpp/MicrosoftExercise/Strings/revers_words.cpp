/**
    Reverse the order of words in a given sentence(an array of characters).

    @file revers_words.cpp
    @author Tamir Cohen
    @version 1.0 14/03/2022
*/

/*
https://www.educative.io/m/reverse-words-in-a-sentence

Solution Explanation

Runtime complexity
The runtime complexity of this solution is linear, O(n).

Position of all the elements in the sentence is changed.

Memory complexity
The memory complexity of this solution is constant, O(1).


Solution Breakdown
Here is how the solution works:

Reverse the string.
Traverse the string and reverse each word in place.
*/

#include <iostream>
#include <string>
#include <cstring>
using namespace std;

/**
    Reverse the order of words in a given sentence.
    @param sentence an array of characters
*/
void reversWords(char sentence[])
{
    char *start = sentence;
    string arr{""};
    string word{""};

    while (*sentence != '\0')
    {
        word += *sentence;

        if (*sentence == ' ') // end of word
        {
            arr = word + arr;
            word = "";
        }

        sentence++;
    }
    // adding the last word
    arr = word + " " + arr;

    // copying the contents of the string to char array
    strcpy(start, arr.c_str());
}

int main()
{
    char str[]{"Hello World my name is tamir"};
    cout << "Str: " << str << endl;
    reversWords(str);
    cout << "Str reversed: " << str << endl;
}