#pragma once
using namespace std;
#include "mammal.h"

class Dog : public Mammal
{
private:
    string m_color;
    string m_bark;

public:
    Dog(string color, string bark);

    string get_color();
    void set_color(string color);

    string get_bark();
    void set_bark(string bark);
};