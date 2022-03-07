#include "farmdog.h"

/* FarmDog class constructor & base class Dog construct */
FarmDog::FarmDog(string color, string bark, string favorite_tree, bool like_cows) : Dog(color, bark)
{
	this->m_favorite_tree = favorite_tree;
	this->m_like_cows = like_cows;
}

string FarmDog::get_favorite_tree() { return this->m_favorite_tree; }
void FarmDog::set_favorite_tree(string favorite_tree) { this->m_favorite_tree = favorite_tree; }

bool FarmDog::get_like_cows() { return this->m_like_cows; }
void FarmDog::set_like_cows(bool like_cows) { this->m_like_cows = like_cows; }

void FarmDog::print()
{
	cout << "---- FarmDog ---" << endl;
	cout << "Water: " << this->get_water_level() << endl;
	cout << "Food: " << this->get_food_level() << endl;
	cout << "Awake: " << ((this->is_awake()) ? "Yes" : "No") << endl;
	cout << "Color: " << this->get_color() << endl;
	cout << "bark: " << this->get_bark() << endl;
	cout << "like cows: " << ((this->m_like_cows) ? "Yes" : "No") << endl;
	cout << "----------------" << endl;
}