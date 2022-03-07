// Zoo.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

using namespace std;
#include <iostream>
#include "seacat.h"
#include "farmdog.h"

int main()
{
    SeaCat c1 = SeaCat("black", "blopblop", false, "tuna");
    SeaCat c2 = SeaCat("gray", "blopblop", false, "tuna");

    FarmDog d1 = FarmDog("white & brown", "miao", "erez", true);
    FarmDog d2 = FarmDog("white & black", "wof wof", "alon", false);

    Animal *zoo[] = {&c1, &c2, &d1, &d2};

    cout << "Welcome to my zoo!\nLest meet all the animals:" << endl;
    for (size_t i = 0; i < 4; i++)
    {
        zoo[i]->print();
    }

    cout << "\nThe animals are hungry let's feed them!" << endl;
    for (size_t i = 0; i < 4; i++)
    {
        zoo[i]->add_food(20);
    }
    for (size_t i = 0; i < 4; i++)
    {
        zoo[i]->print();
    }

    cout << "\nThe animals are tires let's go to sleep!" << endl;
    for (size_t i = 0; i < 4; i++)
    {
        zoo[i]->sleep();
    }
    for (size_t i = 0; i < 4; i++)
    {
        zoo[i]->print();
    }
}
