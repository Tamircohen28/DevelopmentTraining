// GuardiansB.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "Heap.h"
#include "Solider.h"
#define MEM_ERR "\n$> \"" << __FILE__ << "\" \n[" << __LINE__ << "]: Unable to allocate mem!"
#define MANU "$> Enter 1 to add new solider \n$> Enter 2 to update score \n$> Enter 3 to make task \n$> Enter 4 to print table"

template <typename T>
int32_t delete_ptr(Iheap<T> *obj)
{
	if (!obj)
	{
		return -1;
	}

	delete (obj);
	obj = nullptr;
	return 0;
}

template <typename T>
SHeap<T> *Heap_New(size_t uMaxSize)
{
	/* alocate new heap obj on the heap */
	SHeap<T> *Heap_temp = (SHeap<T> *)calloc(1, sizeof(SHeap<T>));

	if (!Heap_temp)
	{
		std::cout << MEM_ERR << std::endl;
		return nullptr;
	}

	// initial values
	Heap_temp->current_size = 0;
	Heap_temp->max_size = uMaxSize;
	Heap_temp->arr = nullptr;

	return Heap_temp;
}

template <typename T>
void Heap_Print(const SHeap<T> *pHeap)
{
	if (!pHeap)
	{
		std::cout << "$> Heap ptr -> nullptr" << std::endl;
		return;
	}

	std::cout << "\n---------- Heap ----------" << std::endl;
	std::cout << "<Max>: " << pHeap->max_size << std::endl;
	std::cout << "<Cur>: " << pHeap->current_size << std::endl;

	if (pHeap->arr != nullptr && pHeap->current_size > 0)
	{
		std::cout << "[";
		for (size_t i = 0; i < pHeap->current_size; i++)
		{
			std::cout << pHeap->arr[i]->GetVal();

			if (i < pHeap->current_size - 1)
			{
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

template <typename T>
EHeapError Heap_Push(SHeap<T> *pHeap, Iheap<T> *pObj)
{
	if (pHeap == nullptr || pObj == nullptr)
	{
		std::cout << "\n[ERR]: 'Heap_Push' func variables cannot be nullptr!" << std::endl;
		return EHeapError::eHeapError_InvalidParams;
	}

	if (Heap_IsFull(pHeap))
	{
		std::cout << "\n[ERR]: 'Heap_Push' func: Heap is full!" << std::endl;
		return EHeapError::eHeapError_Full_Heap;
	}

	// create pointer to new object by allocating memory
	Iheap<T> *temp_pObj = (Iheap<T> *)calloc(1, sizeof(Iheap<T> *));

	if (!temp_pObj)
	{
		std::cout << MEM_ERR << std::endl;
		return EHeapError::eHeapError_Error;
	}
	temp_pObj = pObj;

	// creat array of objects
	Iheap<T> **temp_arr = nullptr;
	if (pHeap->current_size == 0)
	{
		temp_arr = (Iheap<T> **)calloc(1, sizeof(Iheap<T> **));

		if (!temp_arr)
		{
			std::cout << MEM_ERR << std::endl;
			return EHeapError::eHeapError_Error;
		}
		// point array to only variable
		*temp_arr = temp_pObj;
	}
	else
	{
		// realloc free old memory
		temp_arr = (Iheap<T> **)realloc(pHeap->arr, sizeof(Iheap<T> *) * (pHeap->current_size + 1));

		if (!temp_arr)
		{
			std::cout << MEM_ERR << std::endl;
			return EHeapError::eHeapError_Error;
		}
		// insert new variable
		temp_arr[pHeap->current_size] = temp_pObj;
	}

	pHeap->arr = temp_arr;
	pHeap->current_size += 1;
	insert_val(&pHeap);
	return EHeapError::eHeapError_Success;
}

template <typename T>
bool Heap_IsEmpty(const SHeap<T> *pHeap)
{
	return (pHeap->current_size == 0);
}

template <typename T>
bool Heap_IsFull(const SHeap<T> *pHeap)
{
	return (pHeap->current_size == pHeap->max_size);
}

template <typename T>
size_t Heap_GetSize(SHeap<T> *pHeap)
{
	return pHeap->current_size;
}

template <typename T>
void *Heap_PopHead(SHeap<T> **pHeap)
{
	if (Heap_IsEmpty((*pHeap)))
	{
		return nullptr;
	}
	void *return_ptr = nullptr;

	if ((*pHeap)->current_size == 1)
	{
		(*pHeap)->current_size--;
		return_ptr = (*pHeap)->arr[0];
		(*pHeap)->arr = nullptr;
		return return_ptr;
	}

	// Store the minimum value, and remove it from heap
	return_ptr = (*pHeap)->arr[0];
	(*pHeap)->arr[0] = (*pHeap)->arr[(*pHeap)->current_size - 1];
	(*pHeap)->current_size--;
	MinHeapify((*pHeap), 0);

	return return_ptr;
}

template <typename T>
EHeapError Heap_Delete(SHeap<T> **pHeap, del_fnc pfnDataDel)
{

	for (size_t i = 0; i < (*pHeap)->current_size; i++)
	{
		if (pfnDataDel((*pHeap)->ptr[i]) != 0)
		{
			return EHeapError::eHeapError_Error;
		}
	}
	delete ((*pHeap));
	*pHeap = nullptr;
	return EHeapError::eHeapError_Success;
}

template <typename T>
void *Heap_GetHead(const SHeap<T> *pHeap)
{
	if (Heap_IsEmpty(pHeap))
	{
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

/**
 * function to fix the heap after inserting value
 * @param pHeap    pointer to the pointer of The Heap
 * @return (void)  Returns nothing
 */
template <typename T>
void insert_val(SHeap<T> **pHeap)
{
	int i = (*pHeap)->current_size - 1;

	// Fix the min heap property if it is violated
	while (i != 0 && (*pHeap)->arr[parent(i)]->GetVal() > (*pHeap)->arr[i]->GetVal())
	{

		(*pHeap)->arr[i]->Swap((*pHeap)->arr[parent(i)]);
		i = parent(i);
	}
}

template <typename T>
void Heap_Print_Obj(const SHeap<T> *const pHeap)
{
	if (pHeap->arr != nullptr && pHeap->current_size > 0)
	{
		for (size_t i = 0; i < pHeap->current_size; i++)
		{
			pHeap->arr[i]->Print();
		}
	}
	else
	{
		std::cout << "\n[No Objects in the Heap!]" << std::endl;
	}
}

/**
 * A recursive method to heapify a subtree with the root at given index
 * This method assumes that the subtrees are already heapified
 * @param pHeap    pointer to The Heap
 * @param i        index to heapify
 * @return (void)  Returns nothing
 */
template <typename T>
void MinHeapify(SHeap<T> *pHeap, int i)
{
	int l = left(i);
	int r = right(i);
	int smallest = i;

	if (l < pHeap->current_size && pHeap->arr[l]->GetVal() < pHeap->arr[i]->GetVal())
		smallest = l;
	if (r < pHeap->current_size && pHeap->arr[r]->GetVal() < pHeap->arr[smallest]->GetVal())
		smallest = r;
	if (smallest != i)
	{
		pHeap->arr[i]->Swap(pHeap->arr[smallest]);
		MinHeapify(pHeap, smallest);
	}
}

/* Guardians system */
enum Options
{
	E_EMPTY = 0,
	E_NEW_SOLIDER = 1,
	E_UPDATE_SCORE = 2,
	E_SET_TASK = 3,
	E_PRINT_SOLIDERS = 4
};
const int ENUM_ARR[] = {Options::E_SET_TASK, Options::E_NEW_SOLIDER, Options::E_UPDATE_SCORE, Options::E_PRINT_SOLIDERS};

bool is_enum(int val)
{
	for (int i = 0; i < (sizeof(ENUM_ARR) / sizeof(*ENUM_ARR)); i++)
	{
		if (ENUM_ARR[i] == val)
		{
			return true;
		}
	}
	return false;
}

size_t get_action()
{
	size_t option = Options::E_EMPTY;

	while (!is_enum(option))
	{
		std::cout << MANU << std::endl;
		std::cin >> option;
		if (!is_enum(option))
		{
			std::cout << "$> Input not valid try again!\n"
					  << std::endl;
		}
	}

	return option;
}

template <typename T>
void Add_solider(SHeap<T> *Hptr)
{
}

template <typename T>
void Update_score(SHeap<T> *Hptr)
{
}

template <typename T>
void Set_task(SHeap<T> *Hptr)
{
}

int main()
{
	SHeap<int> *Hptr = Heap_New<int>(3);
	size_t option = Options::E_EMPTY;

	while (true)
	{
		option = get_action();

		switch (option)
		{
		case Options::E_NEW_SOLIDER:
		{
			Add_solider(Hptr);
			break;
		}
		case Options::E_UPDATE_SCORE:
		{
			Update_score(Hptr);
			break;
		}
		case Options::E_SET_TASK:
		{
			Set_task(Hptr);
			break;
		}
		case Options::E_PRINT_SOLIDERS:
		{
			Heap_Print_Obj(Hptr);
			break;
		}
		default:
		{
			std::cout << "\n[ERR]: Invalid option!\n"
					  << std::endl;
			break;
		}
		}
	}
}
