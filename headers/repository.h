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

/**
 * Registers an offer addition to the repository history
 */
void RepositoryOfferAdded(Repository *repository, Offer *offer);

/**
 * Registers an offer deletion to the repository history
 */
void RepositoryOfferRemoved(Repository *repository, Offer *offer);

/**
 * Registers an offer update to the repository history
 */
void RepositoryOfferUpdated(Repository *repository, Offer *initialOffer, Offer *newOffer);

/**
 * Undoes the last operation that modified the repository data
 */
int RepositoryUndo(Repository *repository);

/**
 * Redoes the last operation that modified the repository data
 */
int RepositoryRedo(Repository *repository);

/**
 * Clears the repository history
 */
void RepositoryClearHistory(Repository *repository);

/**
 * Creates an operation struct
 */
Operation *OperationCreate(int type, Offer *offer, Offer *initialOffer);

/**
 * Destroys the operation struct
 */
void OperationDestroy(Operation *operation);

#endif //LAB3_4_REPOSITORY_H

