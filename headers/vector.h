//
// Created by Horatiu on 06-Mar-19.
//
#pragma once

typedef void *TElem;

typedef struct _VECTOR
{
    int Size;
    int AllocatedSize;
    TElem *Elements;
} VECTOR;

/**
 * Creates the vector
 */
int VecCreate(VECTOR **Vector);

/**
 * Destroys the vector
 */
int VecDestroy(VECTOR **Vector);

/**
 * Inserts element at the end of the vector
 */
int VecInsertTail(VECTOR *Vector, TElem Value);

/**
 * Inserts element at the beginning of the vector
 */
int VecInsertHead(VECTOR *Vector, TElem Value);

/**
 * Inserts element after the specified index in the vector
 */
int VecInsertAfterIndex(VECTOR *Vector, int Index, TElem Value);

/**
 * Removes the element on the given position
 */
int VecRemoveByIndex(VECTOR *Vector, int Index);

/**
 * Retrieves the value at the given index in the vector
 */
int VecGetValueByIndex(VECTOR *Vector, int Index, TElem *Value);

/**
 * Gets the number of elements stored in the vector
 */
int VecGetCount(VECTOR *Vector);

/**
 * Empties the vector
 */
int VecClear(VECTOR *Vector);

/**
 * Sorts the vector in ascending order using the comparator provided
 */
int VecSort(VECTOR *Vector, int (*compare)(TElem elem1, TElem elem2));