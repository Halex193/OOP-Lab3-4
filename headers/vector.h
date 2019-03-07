//
// Created by Horatiu on 06-Mar-19.
//
#pragma once

typedef void *TElem;

typedef struct _VECTOR
{
    // Members
    int Size;
    int AllocatedSize;
    TElem *Elements;
} VECTOR;

int VecCreate(VECTOR **Vector);

int VecDestroy(VECTOR **Vector);

int VecInsertTail(VECTOR *Vector, TElem Value);

int VecInsertHead(VECTOR *Vector, TElem Value);

int VecInsertAfterIndex(VECTOR *Vector, int Index, TElem Value);

int VecRemoveByIndex(VECTOR *Vector, int Index);

int VecGetValueByIndex(VECTOR *Vector, int Index, TElem *Value);

int VecGetCount(VECTOR *Vector);

int VecClear(VECTOR *Vector);

int VecSort(VECTOR *Vector);