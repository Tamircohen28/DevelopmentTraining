#pragma once

// sharelSchool1TeachersIBIss1O1TamirIGuardianstheap.h 
#ifndef GUARDIANSOFTHEBISS_HEAP_H
#define GUARDIANSOFTHEBISS_HEAP_H 

#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>


/****************************************************************************
* Types Declarations
****************************************************************************/
/**
* The Function frees the memory allocated to pData
*
* @param pData The data to free
* @return (int32t) 0 if the function succeeded, or -1 on failure
*
*/
typedef int32_t(*del_fnc)(void *pData);

/** * The function compares two data objects
*
* @param pObjl The first object
* @param pObj2 The second object
* @return (int32_t) 0 if the objects are equal, 1 if the first is bigger or -1 if the second object is bigger
*
*/
typedef int32_t(*cmp_fnc)(const void *pObjl, const void *pObj2);

/**
* The function prints the data object
* @param pData The data to print
* @return Nothing.
*/
typedef void(*print_fnc)(void* pData);

/****************************************************************************
* Structure Declarations
****************************************************************************/
template<typename T>
struct SHeap {
	T** ptr;
	size_t max_size;
	size_t current_size;
	cmp_fnc compre;
};
//typedef struct _SHeap SHeap;

/****************************************************************************
* Enum Declarations
****************************************************************************/
typedef enum _EHeapError {
	eHeapError_Success,
	eHeapError_Error,
	eHeapError_InvalidParams,
	eHeapError_Empty_Heap, // Signals the heap is empty (e.g. for pop)
	eHeapError_Full_Heap // Signals the heap is full (e.g. for push) 1 EHeapError; 
} EHeapError;

/****************************************************************************
* Function Declarations
****************************************************************************/

/** 
* Allocates and initializes a new Heap.
* The function allocates memory for the new Heap
* In case of an error the function returns a NULL
*
* @param uMaxSize The maximum amount of elements that are allowed to be stored in the Heap.
* @param pfnComparator A function that compares between two elements of the Heap.
* The comparator will be used for ordering the Heap's objects.
* @return (SHeap*)         A pointer to the allocated Heap, or NULL for failure
*/
template<typename T>
SHeap<T>* Heap_New(size_t uMaxSize, cmp_fnc pfnComparator);

/**
* Deletes a complete Heap and it's data
*
*  The function runs on the Heap and deletes its variables and their nodes using
*  the received delete function. After deleting the values the Heap itself is deleted
*
*  @param pHeap                    A pointer to the Heap to delete
*  @param pfnDataDel               A function that defines how to delete an object from the Heap
*
*  @return (EHeapError)            One of the values of EHeapError, indicating
*                                  whether the function succeeded or not.
*/
template<typename T>
EHeapError Heap_Delete(SHeap<T>** pHeap, del_fnc pfnDataDel);

/**
 *  Pushes a new value into the Heap
 *
 *  The function allocate        a new node with a pointer to
 *  the received value and       adds it to the Heap using its
 *  comparator function.
 *
 *  @param pHeap         The Heap to insert the new node into
 *  @param pData         The data to add to the Heap
 *
 * @return (EHeapError) One of the values of EHeapError, indicating
 *                            whether the function succeeded or not.
*/
 template<typename T>
 EHeapError Heap_Push(SHeap<T>* pHeap, void* pData);

/**
*  Checks if the Heap is empty.
*  On error false is returned.
*
*  @param pHeap          The Heap to check
*
*  @return (bool)        true if empty, false otherwise
*/
template<typename T>
bool Heap_IsEmpty(const SHeap<T>* pHeap);

/**
 * Checks if the Heap is full.
 * On error false is returned.
 *
 * @param pHeap          The Heap to check
 *
 * @return (bool)        true if full, false otherwise
 */
template<typename T>
bool Heap_IsFull(const SHeap<T> *pHeap);

/**
*  Returns the current size of the Heap.
*  If a NULL was sent, the Heap is considered empty
*
* @param pHeap               The Heap to get the size of
*
* @return (size_t)           The size of the Heap
*/
template<typename T>
size_t Heap_GetSize(SHeap<T>* pHeap);

/**
* The function returns a pointer to the data at the head of the heap and remove it.
* In case of an error the function returns a NULL
* @param pHeap    The Heap
*
* @return (void*) The data of the wanted node
*/
template<typename T>
void* Heap_PopHead(SHeap<T>** pHeap);

/**
* The function returns a pointer to the data at the head of the heap without removing
* In case of an error the function returns a NULL
*
* @param pHeap    The Heap
*
* @return (void*) The data of the wanted node
*/
template<typename T>
void* Heap_GetHead(const SHeap<T>* pHeap);

/**
* The function prints the data of all the nodes in the heap
*
* @param pHeap            The Heap to print
* @param printFunction    The function to print the data of the nodes
*
* @return Nothing.
*/
template<typename T>
void Heap_Print(const SHeap<T>* pHeap, print_fnc printFunction);

#endif //GUARDIANSOFTHEBISS HEAP H