/* Interface for heap objects */
#pragma once
template<typename T>
class Iheap
{
public:
	virtual T GetVal() = 0;
	virtual void Print() = 0;
	virtual void Swap(Iheap<T>* ptr) = 0;
};

