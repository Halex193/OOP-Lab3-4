//
// Created by Horatiu on 11-Mar-19.
//

#include <assert.h>
#include <stdio.h>
#include "repositoryTest.h"
#include "../headers/repository.h"
#include "../headers/model.h"

int TestVector()
{
    int returnValue = -1;
    int value = 0;
    int* foundValue = &value;
    VECTOR *usedVector = NULL;

    returnValue = VecCreate(&usedVector);
    if (0 != returnValue)
    {
        printf("VecCreate failed!\n");
        goto cleanup;
    }

    int value1 = 10;
    returnValue = VecInsertTail(usedVector, (void*)&value1);
    if (0 != returnValue)
    {
        printf("VecInsertTail failed!\n");
        goto cleanup;
    }

    int value2 = 16;
    returnValue = VecInsertHead(usedVector, (void*)&value2);
    if (0 != returnValue)
    {
        printf("VecInsertHead failed!\n");
        goto cleanup;
    }

    if (VecGetCount(usedVector) != 2)
    {
        printf("Invalid count returned!\n");
        returnValue = -1;
        goto cleanup;
    }

    int value3 = 20;
    returnValue = VecInsertAfterIndex(usedVector, 0, (void*)&value3);
    if (0 != returnValue)
    {
        printf("VecInsertAfterIndex failed!\n");
        goto cleanup;
    }

    returnValue = VecRemoveByIndex(usedVector, 0);
    if (0 != returnValue)
    {
        printf("VecRemoveByIndex failed!\n");
        goto cleanup;
    }

    returnValue = VecGetValueByIndex(usedVector, 0, (void**)&foundValue);
    if (0 != returnValue)
    {
        printf("VecGetValueByIndex failed!\n");
        goto cleanup;
    }

    if (*foundValue != 20)
    {
        printf("Invalid value found at position 0\n");
        returnValue = -1;
        goto cleanup;
    }

    returnValue = VecClear(usedVector);
    if (0 != returnValue)
    {
        printf("VecClear failed!\n");
        goto cleanup;
    }

    if (0 != VecGetCount(usedVector))
    {
        printf("Invalid count after clear\n");
        returnValue = -1;
        goto cleanup;
    }

    cleanup:
    if (NULL != usedVector)
    {
        if (0 != VecDestroy(&usedVector))
        {
            printf("VecDestroy failed!\n");
            returnValue = -1;
        }
    }
    return returnValue;
}

void testRepository()
{
    TestVector();
    Repository *repository = RepoCreate();
    VECTOR *offers = repository->offers;
    assert(VecGetCount(offers) == 0);

    Offer* offer;
    OfferCreate(&offer, "Romania", 12, 12, 12, "seaside", 12000);
    VecInsertTail(offers, offer);
    assert(VecGetCount(offers) == 1);

    Offer* offer2;
    VecGetValueByIndex(offers, 0, (void**)&offer2);
    assert(offer == offer2);

    RepoDestroy(repository);
    printf("Repository test passed!\n");
}
