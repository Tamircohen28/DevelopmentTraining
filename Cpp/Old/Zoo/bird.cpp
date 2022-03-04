// bird.cpp : This file contains the 'bird' class implentation
//

using namespace std;
#include <iostream>
#include "bird.h"

/* Constructor */
Bird::Bird(bool flying) { this->m_flying = flying; }

bool Bird::is_fly() { return this->m_flying; }
void Bird::fly() { this->m_flying = true; }
void Bird::land() {	this->m_flying = false; }