#include "dog.h"

Dog::Dog(string color, string bark)
{
	this->m_color = color;
	this->m_bark = bark;
}

string Dog::get_color() { return this->m_color; }
void Dog::set_color(string color) { this->m_color = color; };

string Dog::get_bark() { return this->m_bark; }
void Dog::set_bark(string bark) { this->m_bark = bark; };