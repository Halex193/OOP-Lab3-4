//
// Created by Horatiu on 06-Mar-19.
//

#include "../headers/vector.h"
#include <stdlib.h>

#define DEFAULT_VECTOR_SIZE 8


int VecExtendSize(VECTOR *);

int VecCreate(VECTOR **Vector)
{
    if (Vector == NULL)
    {
        return -1;
    }
    VECTOR *newVector = (VECTOR *) malloc(sizeof(VECTOR));
    if (newVector == NULL)
    {
        *Vector = NULL;
        return -1;
    }

    newVector->AllocatedSize = DEFAULT_VECTOR_SIZE;
    newVector->Size = 0;
    TElem *elements = (TElem *) malloc(sizeof(TElem) * DEFAULT_VECTOR_SIZE);
    if (elements == NULL)
    {
        *Vector = NULL;
        return -1;
    }
    newVector->Elements = elements;
    *Vector = newVector;
    return 0;
}

int VecDestroy(VECTOR **Vector)
{
    if (Vector == NULL || *Vector == NULL)
    {
        return -1;
    }
    free((*Vector)->Elements);
    free(*Vector);
    *Vector = NULL;
    return 0;
}

int VecInsertTail(VECTOR *Vector, TElem Value)
{
    if (Vector == NULL)
    {
        return -1;
    }
    if (Vector->Size == Vector->AllocatedSize)
    {
        if (VecExtendSize(Vector) == -1)
        {
            return -1;
        }
    }
    Vector->Elements[Vector->Size++] = Value;
    return 0;
}

int VecInsertHead(VECTOR *Vector, TElem Value)
{
    if (Vector == NULL)
    {
        return -1;
    }

    if (Vector->Size == Vector->AllocatedSize)
    {
        if (VecExtendSize(Vector) == -1)
        {
            return -1;
        }
    }
    const int size = Vector->Size;
    TElem *elements = Vector->Elements;
    for (int i = size; i > 0; i--)
    {
        elements[i] = elements[i - 1];
    }
    elements[0] = Value;
    Vector->Size++;
    return 0;
}

int VecInsertAfterIndex(VECTOR *Vector, int Index, TElem Value)
{
    if (Vector == NULL)
    {
        return -1;
    }

    if (Index < 0 || Index > Vector->Size - 1)
    {
        return -1;
    }

    if (Vector->Size == Vector->AllocatedSize)
    {
        if (VecExtendSize(Vector) == -1)
        {
            return -1;
        }
    }

    const int size = Vector->Size;
    TElem *elements = Vector->Elements;
    for (int i = size; i > Index + 1; i--)
    {
        elements[i] = elements[i - 1];
    }
    elements[Index + 1] = Value;
    Vector->Size++;

    return 0;
}

int VecRemoveByIndex(VECTOR *Vector, int Index)
{
    if (Vector == NULL)
    {
        return -1;
    }

    if (Index < 0 || Index >= Vector->Size)
    {
        return -1;
    }

    const int size = Vector->Size;
    TElem *elements = Vector->Elements;
    for (int i = Index; i < size - 1; i++)
    {
        elements[i] = elements[i + 1];
    }
    Vector->Size--;

    if (Vector->Size < Vector->AllocatedSize / 4)
    {
        elements = realloc(Vector->Elements, sizeof(TElem) * (Vector->AllocatedSize / 2));
        if (elements == NULL)
        {
            return -1;
        }
        Vector->AllocatedSize = Vector->AllocatedSize / 2;
        Vector->Elements = elements;
    }

    return 0;
}

int VecGetValueByIndex(VECTOR *Vector, int Index, TElem *Value)
{
    if (Vector == NULL)
    {
        return -1;
    }

    if (Index < 0 || Index >= Vector->Size)
    {
        return -1;
    }
    *Value = Vector->Elements[Index];
    return 0;
}

int VecGetCount(VECTOR *Vector)
{
    if (Vector == NULL)
    {
        return -1;
    }

    return Vector->Size;
}

int VecClear(VECTOR *Vector)
{
    if (Vector == NULL)
    {
        return -1;
    }
    Vector->Size = 0;
    return 0;
}

int VecSort(VECTOR *Vector, int (*compare)(TElem elem1, TElem elem2))
{
    if (Vector == NULL)
    {
        return -1;
    }
    const int size = Vector->Size;
    TElem *elements = Vector->Elements;
    for (int i = 0; i < size - 1; i++)
    {
        for (int j = i + 1; j < size; j++)
        {
            if (compare(elements[i], elements[j]) > 0)
            {
                TElem temp = elements[i];
                elements[i] = elements[j];
                elements[j] = temp;
            }
        }
    }
    return 0;
}

int VecExtendSize(VECTOR *Vector)
{
    TElem *elements = realloc(Vector->Elements, sizeof(TElem) * (Vector->AllocatedSize * 2));
    if (elements == NULL)
    {
        return -1;
    }

    Vector->AllocatedSize = Vector->AllocatedSize * 2;
    Vector->Elements = elements;
    return 0;
}