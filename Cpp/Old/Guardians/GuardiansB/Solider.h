#pragma once
#include "Iheap.h"
#include <string>

template<typename T>
class Solider : public Iheap<T>
{
public:
	T points;
	std::string name;
	std::string unit;
	std::string id;
	
	Solider() {
		this->points = 0;
		this->name = "None";
		this->unit = "Matzov";
		this->id = "123456789";
	}

	Solider(T points, std::string name, std::string unit, std::string id) {
		this->points = points;
		this->name = name;
		this->unit = unit;
		this->id = id;
	}

	T GetVal() { return this->points; }

	void Print() {
		std::cout << "\n----- Solider -----" << std::endl;
		std::cout << "Name: " << this->name << std::endl;
		std::cout << "Unit: " << this->unit << std::endl;
		std::cout << "ID: " << this->id << std::endl;
		std::cout << "Score: " << this->points << std::endl;
	}

	void Swap(Iheap<T>* ptr) {
		Solider<T> temp = *this;
		*this = *(Solider<T> *)ptr;
		*(Solider<T>*)ptr = temp;
	}
};
