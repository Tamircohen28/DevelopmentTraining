// GuardiansA.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "Heap.h"
#define MEM_ERR "\n$> \""<< __FILE__ << "\" \n[" << __LINE__ << "]: Unable to allocate mem!"

void print_var(void* pData) {
	std::cout << *(int*)pData;
}

int32_t delete_ptr(void* pData) {
	if (!pData) {
		return -1;
	}

	free(pData);
	pData = nullptr;
	return 0;
}

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
	insert_val(&pHeap);
	return eHeapError_Success;
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
void* Heap_PopHead(SHeap<T>** pHeap) {
	if (Heap_IsEmpty((*pHeap))) {
		return nullptr;
	}
	T* return_ptr = nullptr;

	if ((*pHeap)->current_size == 1)
	{
		(*pHeap)->current_size--;
		return_ptr = (*pHeap)->ptr[0];
		(*pHeap)->ptr = nullptr;
		return return_ptr;
	}

	// Store the minimum value, and remove it from heap 
	return_ptr = (*pHeap)->ptr[0];
	(*pHeap)->ptr[0] = (*pHeap)->ptr[(*pHeap)->current_size - 1];
	(*pHeap)->current_size--;
	MinHeapify((*pHeap), 0);

	return return_ptr;
}

template<typename T>
EHeapError Heap_Delete(SHeap<T>** pHeap, del_fnc pfnDataDel) {

	for (size_t i = 0; i < (*pHeap)->current_size; i++)
	{
		if (pfnDataDel((*pHeap)->ptr[i]) != 0) {
			return eHeapError_Error;
		}
	}
	delete((*pHeap));
	*pHeap = nullptr;
	return eHeapError_Success;
}

template<typename T>
void* Heap_GetHead(const SHeap<T>* pHeap) {
	if (Heap_IsEmpty(pHeap)) {
		return nullptr;
	}
	return pHeap->ptr[0];
}

/* From here this are function  that i added that are not included
in the given in the .h file
*/

// to get index of the parent
int parent(int i) { return (i - 1) / 2; }

// to get index of left child of node at index i 
int left(int i) { return (2 * i + 1); }

// to get index of right child of node at index i 
int right(int i) { return (2 * i + 2); }

// A utility function to swap two elements 
void swap(int* x, int* y)
{
	int temp = *x;
	*x = *y;
	*y = temp;
}

/**
* function to fix the heap after inserting value
* @param pHeap    pointer to the pointer of The Heap
* @return (void)  Returns nothing
*/
template<typename T>
void insert_val(SHeap<T>** pHeap)
{
	int i = (*pHeap)->current_size - 1;

	// Fix the min heap property if it is violated 
	while (i != 0 && *(*pHeap)->ptr[parent(i)] > * (*pHeap)->ptr[i])
	{
		swap((*pHeap)->ptr[i], (*pHeap)->ptr[parent(i)]);
		i = parent(i);
	}
}


/**
* A recursive method to heapify a subtree with the root at given index
* This method assumes that the subtrees are already heapified
* @param pHeap    pointer to The Heap
* @param i        index to heapify
* @return (void)  Returns nothing
*/
template<typename T>
void MinHeapify(SHeap<T>* pHeap, int i)
{
	int l = left(i);
	int r = right(i);
	int smallest = i;

	if (l < pHeap->current_size && *pHeap->ptr[l] < *pHeap->ptr [i])
		smallest = l;
	if (r < pHeap->current_size && *pHeap->ptr[r] < *pHeap->ptr [smallest])
		smallest = r;
	if (smallest != i)
	{
		swap(pHeap->ptr[i], pHeap->ptr[smallest]);
		MinHeapify(pHeap, smallest);
	}
}

int main()
{
	SHeap<int>* Hptr = Heap_New<int>(10, Heap_cmp);
	int a = 4; 
	int b = 2; 
	int c = 1;
	int d = 9;
	int e = 3;
	
	Heap_Push(Hptr, &a);
	Heap_Push(Hptr, &b);
	Heap_Push(Hptr, &c);
	Heap_Print(Hptr, print_var);
	Heap_PopHead(&Hptr);
	std::cout << "\n$> Poped Head!" << std::endl;
	Heap_Print(Hptr, print_var);
	Heap_Push(Hptr, &d);
	Heap_Push(Hptr, &e);
	Heap_Print(Hptr, print_var);
	Heap_Delete(&Hptr, delete_ptr);
	std::cout << "\n$> Delete heap!" << std::endl;
	Heap_Print(Hptr, print_var);
	return 0;
}


