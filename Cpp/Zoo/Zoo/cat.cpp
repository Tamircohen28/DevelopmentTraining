#include "cat.h"

/* Cat constructor & base class Mammal construct */
Cat::Cat(string color, string miaow, bool breastfeed) : Mammal(breastfeed) {
	this->m_color = color;
	this->m_miaow = miaow;
}

string Cat::get_color() { return this->m_color;  }
void Cat::set_color(string color) { this->m_color = color; }

string Cat::get_miaow() { return this->m_miaow; }
void Cat::set_miaow(string miaow) { this->m_miaow = miaow; }
