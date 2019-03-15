/*
 * Udrea Horațiu 917
 *
 * 3. Tourism Agency
 */

#include <stdio.h>
#include "headers/vector.h"
#include "headers/ui.h"
#include "headers/model.h"
#include "headers/repository.h"
//0 -> operation based, 1 -> list based



int main()
{
    setbuf(stdout, 0);
    Repository *repository = RepoCreate();
    run(repository);
    RepoDestroy(repository);
    return 0;
}
