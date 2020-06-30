#include "seacat.h"

/* SeaCat constructor & base class Cat construct */
SeaCat::SeaCat(string color, string miaow, bool breastfeed, string favorite_fish, bool salt_water) :
	Cat(color, miaow, breastfeed) {
	this->m_favorite_fish = favorite_fish;
	this->m_salt_water = salt_water;
}

string SeaCat::get_favorite_fish() { return this->m_favorite_fish; }
void SeaCat::set_favorite_fish(string favorite_fish) { this->m_favorite_fish = favorite_fish; }

bool SeaCat::get_salt_water() { return this->m_salt_water; }
void SeaCat::set_salt_water(bool salt_water) { this->m_salt_water = salt_water; }

void SeaCat::print() {
	cout << "---- SeaCat ----" << endl;
	cout << "Water: "  << this->get_water_level() << endl;
	cout << "Food: "   << this->get_food_level() << endl;
	cout << "Awake: "  << ((this->is_awake()) ? "Yes" : "No") << endl;
	cout << "Color: " << this->get_color() << endl;
	cout << "miaow: " << this->get_miaow() << endl;
	cout << "favoite fish: " << this->m_favorite_fish << endl;
	cout << "----------------" << endl;
}