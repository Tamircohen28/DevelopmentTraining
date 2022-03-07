#pragma once
using namespace std;
#include "mammal.h"

class Cat : public Mammal
{
private:
    string m_color;
    string m_miaow;

public:
    Cat(string color, string miaow, bool breastfeed);

    string get_color();
    void set_color(string color);

    string get_miaow();
    void set_miaow(string miaow);
};