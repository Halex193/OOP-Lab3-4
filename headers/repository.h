//
// Created by Horatiu on 06-Mar-19.
//

#ifndef LAB3_4_REPOSITORY_H
#define LAB3_4_REPOSITORY_H

#include "vector.h"
#include "model.h"
// 0 -> operation based, 1 -> list based
#define UndoRedoType 1

typedef struct _Repository
{
    VECTOR *offers;
    VECTOR *history;
    int historyIndex;
    int historyType; // 0 -> operation based, 1 -> list based
} Repository;

typedef struct _Operation
{
    int type; // 0 -> add, 1 -> remove, 2 -> update
    Offer *offer;
    Offer *initialOffer;
} Operation;

/**
 * Created the vector that will hold the application's offers
 * @return The created vector
 */
Repository *RepoCreate();

/**
 * Frees the memory associated with the vector and the offers of the program
 * @param vector The vector that will be freed
 */
void RepoDestroy(Repository *repository);

void RepositoryOfferAdded(Repository *repository, Offer *offer);

void RepositoryOfferRemoved(Repository *repository, Offer *offer);

void RepositoryOfferUpdated(Repository *repository, Offer *initialOffer, Offer *newOffer);

int RepositoryUndo(Repository *repository);

int RepositoryRedo(Repository *repository);

void RepositoryClearHistory(Repository *repository);

Operation *OperationCreate(int type, Offer *offer, Offer *initialOffer);

void OperationDestroy(Operation *operation);

#endif //LAB3_4_REPOSITORY_H

