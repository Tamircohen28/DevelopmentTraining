#pragma once
#include <string>
#include <iostream>

class Animal
{
private:
    size_t m_food_level;  // between 0 - 100
    size_t m_water_level; // between 0 - 100
    bool m_awake;

public:
    Animal(size_t food_level = 50, size_t water_level = 50, bool awake = true);

    void add_food(size_t food_quantity);
    size_t get_food_level();

    void add_water(size_t water_quantity);
    size_t get_water_level();

    bool is_awake();
    void wake();
    void sleep();

    // Pure Virtual Function
    virtual void print() = 0;
};
