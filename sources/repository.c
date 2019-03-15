//
// Created by Horatiu on 06-Mar-19.
//

#include <stdlib.h>
#include "../headers/repository.h"
#include "../headers/model.h"

void operationAdded(Repository *repository, const Operation *operation);

Repository *RepoCreate()
{
    Repository *repository = (Repository *) malloc(sizeof(Repository));
    repository->historyIndex = -1;
    repository->historyType = UndoRedoType;
    VecCreate(&repository->offers);
    VecCreate(&repository->history);
    
    if (repository->historyType == 1)
    {
        VECTOR *vector;
        VecCreate(&vector);
        VecInsertTail(repository->history, vector);
        repository->historyIndex = 0;
    }
    return repository;
}

void RepoDestroy(Repository *repository)
{
    VECTOR *offers = repository->offers;
    for (int i = 0; i < VecGetCount(offers); i++)
    {
        Offer *offer;
        VecGetValueByIndex(offers, i, (void **) &offer);
        OfferDestroy(&offer);
    }
    VecDestroy(&offers);

    if (repository->historyType == 0)
    {
        VECTOR *history = repository->history;
        for (int i = 0; i < VecGetCount(history); i++)
        {
            Operation *operation;
            VecGetValueByIndex(history, i, (void **) &operation);
            OperationDestroy(operation);
            operation = NULL;
        }
        VecDestroy(&history);
    }
    else if (repository->historyType == 1)
    {
        VECTOR *history = repository->history;
        for (int i = 0; i < VecGetCount(history); i++)
        {
            VECTOR *vector;
            VecGetValueByIndex(history, i, (void **) &vector);

            for (int j = 0; j < VecGetCount(vector); j++)
            {
                Offer *offer;
                VecGetValueByIndex(vector, j, (void **) &offer);
                OfferDestroy(&offer);
            }

            VecDestroy(&vector);
        }
        VecDestroy(&history);
    }
    free(repository);
}

void operationAdded(Repository *repository, const Operation *operation)
{
    VECTOR *history = repository->history;
    int initialSize = VecGetCount(history);
    for (int i = initialSize - 1; i > repository->historyIndex; i--)
    {
        Operation *oldOperation;
        VecGetValueByIndex(history, i, (void **) &oldOperation);
        OperationDestroy(oldOperation);
        VecRemoveByIndex(history, i);
    }
    VecInsertTail(history, (void *) operation);
    repository->historyIndex++;
}

void saveRepositoryState(Repository *repository)
{
    VECTOR *history = repository->history;
    int initialSize = VecGetCount(history);
    for (int i = initialSize - 1; i > repository->historyIndex; i--)
    {
        VECTOR *vector;
        VecGetValueByIndex(history, i, (void **) &vector);

        for (int j = 0; j < VecGetCount(vector); j++)
        {
            Offer *offer;
            VecGetValueByIndex(vector, j, (void **) &offer);
            OfferDestroy(&offer);
        }

        VecDestroy(&vector);
        VecRemoveByIndex(history, i);
    }
    VECTOR *offers = repository->offers;
    VECTOR *vector;
    VecCreate(&vector);
    for (int i = 0; i < VecGetCount(offers); i++)
    {
        Offer *offer;
        VecGetValueByIndex(offers, i, (void **) &offer);
        VecInsertTail(vector, (void *) OfferCopy(offer));
    }
    VecInsertTail(history, (void *) vector);
    repository->historyIndex++;
}

void restoreRepositoryState(Repository *repository, int historyIndex)
{
    VECTOR *offers = repository->offers;
    for (int i = 0; i < VecGetCount(offers); i++)
    {
        Offer *offer;
        VecGetValueByIndex(offers, i, (void **) &offer);
        OfferDestroy(&offer);
    }
    VecClear(offers);
    VECTOR *newState;
    VecGetValueByIndex(repository->history, historyIndex, (void **) &newState);
    for (int i = 0; i < VecGetCount(newState); i++)
    {
        Offer *offer;
        VecGetValueByIndex(newState, i, (void **) &offer);
        VecInsertTail(offers, OfferCopy(offer));
    }
}

void RepositoryOfferAdded(Repository *repository, Offer *offer)
{
    if (repository->historyType == 1)
    {
        saveRepositoryState(repository);
        return;
    }
    Operation *operation = OperationCreate(0, offer, NULL);
    operationAdded(repository, operation);

}

void RepositoryOfferRemoved(Repository *repository, Offer *offer)
{
    if (repository->historyType == 1)
    {
        saveRepositoryState(repository);
        return;
    }
    Operation *operation = OperationCreate(1, offer, NULL);
    operationAdded(repository, operation);
}

void RepositoryOfferUpdated(Repository *repository, Offer *initialOffer, Offer *newOffer)
{
    if (repository->historyType == 1)
    {
        saveRepositoryState(repository);
        return;
    }
    Operation *operation = OperationCreate(1, newOffer, initialOffer);
    operationAdded(repository, operation);
}

int RepositoryUndo(Repository *repository)
{
    if (repository->historyType == 1)
    {
        if (repository->historyIndex == 0)
            return 0;
        restoreRepositoryState(repository, --repository->historyIndex);
        return 1;
    }
    if (repository->historyIndex == -1)
    {
        return 0;
    }
    Operation *operation;
    VecGetValueByIndex(repository->history, repository->historyIndex--, (void **) &operation);
    if (operation->type == 0)
    {
        VECTOR *offers = repository->offers;
        Offer *offer = operation->offer;
        for (int i = 0; i < VecGetCount(offers); i++)
        {
            Offer *storedOffer;
            VecGetValueByIndex(offers, i, (void **) &storedOffer);
            if (OfferEquals(offer, storedOffer))
            {
                VecRemoveByIndex(offers, i);
                OfferDestroy(&storedOffer);
                return 1;
            }
        }
        return 0;
    }
    else if (operation->type == 1)
    {
        VECTOR *offers = repository->offers;
        Offer *offer = OfferCopy(operation->offer);
        for (int i = 0; i < VecGetCount(offers); i++)
        {
            Offer *storedOffer;
            VecGetValueByIndex(offers, i, (void **) &storedOffer);
            if (OfferEquals(offer, storedOffer))
            {
                OfferDestroy(&offer);
                return 0;
            }
        }
        VecInsertTail(offers, offer);
        return 1;
    }
    else if (operation->type == 2)
    {
        VECTOR *offers = repository->offers;
        Offer *offer = OfferCopy(operation->initialOffer);
        for (int i = 0; i < VecGetCount(offers); i++)
        {
            Offer *storedOffer;
            VecGetValueByIndex(offers, i, (void **) &storedOffer);
            if (OfferEquals(offer, storedOffer))
            {
                VecRemoveByIndex(offers, i);
                VecInsertTail(offers, offer);
                OfferDestroy(&storedOffer);
                return 1;
            }
        }
        OfferDestroy(&offer);
        return 0;
    }
    return 0;
}

int RepositoryRedo(Repository *repository)
{
    if (repository->historyType == 1)
    {
        if (repository->historyIndex == VecGetCount(repository->history) - 1)
            return 0;
        restoreRepositoryState(repository, ++repository->historyIndex);
        return 1;
    }
    if (repository->historyIndex == VecGetCount(repository->history) - 1)
    {
        return 0;
    }
    Operation *operation;
    VecGetValueByIndex(repository->history, ++repository->historyIndex, (void **) &operation);
    if (operation->type == 1)
    {
        VECTOR *offers = repository->offers;
        Offer *offer = operation->offer;
        for (int i = 0; i < VecGetCount(offers); i++)
        {
            Offer *storedOffer;
            VecGetValueByIndex(offers, i, (void **) &storedOffer);
            if (OfferEquals(offer, storedOffer))
            {
                VecRemoveByIndex(offers, i);
                OfferDestroy(&storedOffer);
                return 1;
            }
        }
        return 0;
    }
    else if (operation->type == 0)
    {
        VECTOR *offers = repository->offers;
        Offer *offer = OfferCopy(operation->offer);
        for (int i = 0; i < VecGetCount(offers); i++)
        {
            Offer *storedOffer;
            VecGetValueByIndex(offers, i, (void **) &storedOffer);
            if (OfferEquals(offer, storedOffer))
            {
                OfferDestroy(&offer);
                return 0;
            }
        }
        VecInsertTail(offers, offer);
        return 1;
    }
    else if (operation->type == 2)
    {
        VECTOR *offers = repository->offers;
        Offer *offer = OfferCopy(operation->offer);
        for (int i = 0; i < VecGetCount(offers); i++)
        {
            Offer *storedOffer;
            VecGetValueByIndex(offers, i, (void **) &storedOffer);
            if (OfferEquals(offer, storedOffer))
            {
                VecRemoveByIndex(offers, i);
                VecInsertTail(offers, offer);
                OfferDestroy(&storedOffer);
                return 1;
            }
        }
        OfferDestroy(&offer);
        return 0;
    }
    return 0;
}

Operation *OperationCreate(int type, Offer *offer, Offer *initialOffer)
{
    Operation *operation = (Operation *) malloc(sizeof(Operation));
    operation->type = type;
    operation->offer = OfferCopy(offer);
    operation->initialOffer = NULL;
    if (initialOffer != NULL)
        operation->initialOffer = OfferCopy(initialOffer);
    return operation;
}

void OperationDestroy(Operation *operation)
{
    OfferDestroy(&operation->offer);
    OfferDestroy(&operation->initialOffer);
    free(operation);
}

void RepositoryClearHistory(Repository *repository)
{
    if (repository->historyType == 1)
    {
        VECTOR *history = repository->history;
        int initialSize = VecGetCount(history);
        for (int i = initialSize - 2; i >= 0; i--)
        {
            VECTOR *vector;
            VecGetValueByIndex(history, i, (void **) &vector);

            for (int j = 0; j < VecGetCount(vector); j++)
            {
                Offer *offer;
                VecGetValueByIndex(vector, j, (void **) &offer);
                OfferDestroy(&offer);
            }
            VecDestroy(&vector);

            VecRemoveByIndex(history, i);
        }
        repository->historyIndex = 0;
        return;
    }
    VECTOR *history = repository->history;
    int initialSize = VecGetCount(history);
    for (int i = initialSize - 1; i >= 0; i--)
    {
        Operation *oldOperation;
        VecGetValueByIndex(history, i, (void **) &oldOperation);
        OperationDestroy(oldOperation);
        VecRemoveByIndex(history, i);
    }
    repository->historyIndex = -1;
}
