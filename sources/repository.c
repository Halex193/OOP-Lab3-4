//
// Created by Horatiu on 06-Mar-19.
//

#include "../headers/repository.h"
#include "../headers/model.h"

VECTOR *RepoCreate()
{
    VECTOR *vector;
    VecCreate(&vector);
    return vector;
}

void RepoDestroy(VECTOR *vector)
{
    for (int i = 0; i < VecGetCount(vector); i++)
    {
        Offer *offer;
        VecGetValueByIndex(vector, i, (void **) &offer);
        OfferDestroy(&offer);
    }
    VecDestroy(&vector);
}
