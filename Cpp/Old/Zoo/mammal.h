#pragma once
#include "animal.h"

class Mammal : public Animal
{
private:
    bool m_breastfeed;

public:
    Mammal(bool breastfeed = true);

    bool is_breastfeed();
    void start_breastfeed();
    void end_breastfeed();
};