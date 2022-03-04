// mammal.cpp : This file contains the 'mammal' class implentation
//

#include "mammal.h"

/* Constructor */
Mammal::Mammal(bool breastfeed) { this->m_breastfeed = breastfeed; }

bool Mammal::is_breastfeed() { return this->m_breastfeed; }
void Mammal::start_breastfeed() { this->m_breastfeed = true; }
void Mammal::end_breastfeed() { this->m_breastfeed = false; }
