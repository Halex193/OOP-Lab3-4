//
// Created by Horatiu on 11-Mar-19.
//

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "controllerTest.h"
#include "../headers/repository.h"
#include "../headers/controller.h"
#include "../headers/model.h"

void testController()
{
    Repository *repository = RepoCreate();
    VECTOR *offers = repository->offers;

    ControllerPopulate(repository);
    assert(VecGetCount(offers) == 10);

    ControllerAdd(repository, "Chd", 11, 12, 2016, "mountain", 1300);
    assert(VecGetCount(offers) == 11);

    ControllerUpdate(repository, "Chd", 11, 12, 2016, "seaside", 1300);
    assert(VecGetCount(offers) == 11);

    ControllerRemove(repository, "Chd", 11, 12, 2016);
    assert(VecGetCount(offers) == 10);

    ControllerAdd(repository, "Chd", 11, 12, 2016, "mountain", 1300);
    VECTOR* output = ControllerList(repository, "Ch");
    assert(VecGetCount(output) == 2);

    Offer *offer;
    VecGetValueByIndex(output, 0, (void**)&offer);
    assert(strcmp(offer->destination, "Chad") == 0);

    VecGetValueByIndex(output, 1, (void **) &offer);
    assert(strcmp(offer->destination, "Chd") == 0);

    VecDestroy(&output);

    ControllerUndo(repository);
    assert(VecGetCount(offers) == 10);

    ControllerUndo(repository);
    assert(VecGetCount(offers) == 11);

    ControllerRedo(repository);
    assert(VecGetCount(offers) == 10);

    assert(RepositoryUndo(repository));
    assert(RepositoryUndo(repository));

    output = ControllerList(repository, "Chd");
    VecGetValueByIndex(output, 0, (void**)&offer);
    assert(strcmp(offer->type, "mountain") == 0);

    assert(RepositoryUndo(repository));
    assert(!RepositoryUndo(repository));


    RepoDestroy(repository);
    printf("Controller test passed!\n");
}
