#include "pigeon.h"

/* constructor of pigeon and bird */
Pigeon::Pigeon(string color, bool loves_bread, bool flying) : Bird(flying) {
	this->m_color = color;
	this->m_loves_bread = loves_bread;
}

string Pigeon::get_color() { return this->m_color; }
void Pigeon::set_color(string color) { this->m_color = color; }

bool Pigeon::get_bread() { return this->m_loves_bread; }
void  Pigeon::set_bread(bool loves_bread) { this->m_loves_bread = loves_bread; }