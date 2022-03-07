// Aaimal.cpp : This file contains the 'Animal' class implentation
//

using namespace std;
#include <iostream>
#include "animal.h"
#define FOOD_MAX 100
#define WATER_MAX 100

/*
Animal Class Implentation
*/
// Constructor
Animal::Animal(size_t food_level, size_t water_level, bool awake)
{
    this->m_food_level = food_level;
    this->m_water_level = water_level;
    this->m_awake = awake;
}

void Animal::add_food(size_t food_quantity)
{
    // reached max
    if (this->m_food_level + food_quantity > FOOD_MAX)
    {
        this->m_food_level = FOOD_MAX;
    }
    else
    {
        this->m_food_level += food_quantity;
    }
}

void Animal::add_water(size_t water_quantity)
{
    // reached max
    if (this->m_water_level + water_quantity > WATER_MAX)
    {
        this->m_water_level = WATER_MAX;
    }
    else
    {
        this->m_water_level += water_quantity;
    }
}

size_t Animal::get_food_level() { return this->m_food_level; }
size_t Animal::get_water_level() { return this->m_water_level; }

bool Animal::is_awake() { return this->m_awake; }
void Animal::wake() { this->m_awake = true; }
void Animal::sleep() { this->m_awake = false; }
