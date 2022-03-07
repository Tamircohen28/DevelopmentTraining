#pragma once
#include "cat.h"

class SeaCat : public Cat
{
private:
    string m_favorite_fish;
    bool m_salt_water;

public:
    SeaCat(string color, string miaow, bool breastfeed, string favorite_fish, bool salt_water = true);

    string get_favorite_fish();
    void set_favorite_fish(string favorite_fish);

    bool get_salt_water();
    void set_salt_water(bool salt_water);

    // virtual functio  of 'animal'
    void print() override;
};