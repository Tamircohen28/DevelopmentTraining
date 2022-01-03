#pragma once
#include "animal.h"

class Bird : public Animal
{
private:
    bool m_flying;
 
public:
    Bird(bool flying);
    
    bool is_fly();
    void fly();
    void land();
};