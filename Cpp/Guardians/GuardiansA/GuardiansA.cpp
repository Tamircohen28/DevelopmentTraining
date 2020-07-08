// GuardiansA.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "Heap.h"
#define MEM_ERR "\n$> \""<< __FILE__ << "\" \n[" << __LINE__ << "]: Unable to allocate mem!"

int32_t Heap_cmp(const void* pObjl, const void* pObj2) {
	if (*(int *)pObjl == *(int*)pObj2)
	{
		return 0;
	}
	else if (*(int*)pObjl > *(int*)pObj2)
	{
		return 1;
	}
	return -1;
}

template<typename T>
SHeap<T>* Heap_New(size_t uMaxSize, cmp_fnc pfnComparator) {
	SHeap<T>* temp = (SHeap<T>*)calloc(1, sizeof(SHeap<T>));

	if (!temp) {
		std::cout << MEM_ERR << std::endl;
		return nullptr;
	}

	temp->current_size = 0;
	temp->max_size = uMaxSize;
	temp->compre = pfnComparator;
	temp->ptr = nullptr;

	return temp;
}

void print_var(void* pData) {
	std::cout << *(int*)pData;
}

template<typename T>
void Heap_Print(const SHeap<T>* pHeap, print_fnc printFunction) {
	if (!pHeap) {
		std::cout << "$> Heap ptr -> nullptr" << std::endl;
		return;
	}

	if (!printFunction) {
		std::cout << "[ERR]: 'Heap_Print' func variable 'printFunction' cannot be nullptr!" << std::endl;
		return;
	}

	std::cout << "\n---------- Heap ----------" << std::endl;
	std::cout << "<Max>: " << pHeap->max_size << std::endl;
	std::cout << "<Cur>: " << pHeap->current_size << std::endl;

	if (pHeap->ptr != nullptr && pHeap->current_size > 0) {
		std::cout << "[";
		for (size_t i = 0; i < pHeap->current_size; i++)
		{
			printFunction(pHeap->ptr[i]);
			
			if (i < pHeap->current_size - 1) {
				std::cout << ", ";
			}
		}
		std::cout << "]" << std::endl;
		std::cout << "--------------------------" << std::endl;
	}
	else
	{
		std::cout << "[Heap array is Empty]" << std::endl;
	}
}

template<typename T>
EHeapError Heap_Push(SHeap<T>* pHeap, void* pData)
{
	if (pHeap == nullptr || pData == nullptr) {
		std::cout << "[ERR]: 'Heap_Push' func variables cannot be nullptr!" << std::endl;
		return eHeapError_InvalidParams;
	}

	if (Heap_IsFull(pHeap)) {
		std::cout << "[ERR]: 'Heap_Print' func: Heap is full!" << std::endl;
		return eHeapError_Full_Heap;
	}

	// create pointer to value by allocating memory
	T* temp_pData = (T*)calloc(1, sizeof(T*)); // 

	if (!temp_pData) {
		std::cout << MEM_ERR << std::endl;
		return eHeapError_Error;
	}
	*temp_pData = *(T*)pData;

	T** temp = nullptr;
	if (pHeap->current_size == 0) {
		temp = (T**)calloc(1, sizeof(T**));

		if (!temp) {
			std::cout << MEM_ERR << std::endl;
			return eHeapError_Error;
		}
		*temp = temp_pData;
	}
	else
	{
		// realloc free old memory
		temp = (T**)realloc(pHeap->ptr, sizeof(T*) * (pHeap->current_size + 1));

		if (!temp) {
			std::cout << MEM_ERR << std::endl;
			return eHeapError_Error;
		}
		temp[pHeap->current_size] = temp_pData;
	}

	pHeap->ptr = temp;
	pHeap->current_size += 1;
	return eHeapError_Success;
}


size_t get_index(void** pData, size_t value) {
	size_t index = 0;
	while (pData)
	{
		if (value < (size_t)(*pData)) {
			return index;
		}
		index++;
		pData++;
	}
	return index;
}


template<typename T>
bool Heap_IsEmpty(const SHeap<T>* pHeap) {
	return (pHeap->current_size == 0);
}

template<typename T>
bool Heap_IsFull(const SHeap<T>* pHeap) {
	return (pHeap->current_size == pHeap->max_size);
}

template<typename T>
size_t Heap_GetSize(SHeap<T>* pHeap) {
	return pHeap->current_size;
}

template<typename T>
void* Heap_GetHead(const SHeap<T>* pHeap) {
	if (Heap_IsEmpty(pHeap)) {
		return nullptr;
	}
	return pHeap->ptr[0];
}

int main()
{
	SHeap<int>* Hptr = Heap_New<int>(1, Heap_cmp);
	int a = 5; // addr a: 1000, a = 5
	int b = 10; // addr a: 1000, a = 5
	int* p = &a; // addr p: 2000,  p = 1000, *p(1000) = 5
	Heap_Push(Hptr, &a);
	Heap_Push(Hptr, &b);
	Heap_Print(Hptr, print_var);

	return 0;
}

