//
// Created by Horatiu on 06-Mar-19.
//

#include "../headers/repository.h"
#include "../headers/model.h"

Repository RepoCreate()
{
    Repository repository;
    VecCreate(&repository.offers);
    return repository;
}

void RepoDestroy(Repository repository)
{
    VECTOR *offers = repository.offers;
    for (int i = 0; i < VecGetCount(offers); i++)
    {
        Offer *offer;
        VecGetValueByIndex(offers, i, (void **) &offer);
        OfferDestroy(&offer);
    }
    VecDestroy(&offers);
}
