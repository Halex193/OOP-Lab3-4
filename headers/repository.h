//
// Created by Horatiu on 06-Mar-19.
//

#ifndef LAB3_4_REPOSITORY_H
#define LAB3_4_REPOSITORY_H

#include "vector.h"
/**
 * Created the vector that will hold the application's offers
 * @return The created vector
 */
VECTOR *RepoCreate();

/**
 * Frees the memory associated with the vector and the offers of the program
 * @param vector The vector that will be freed
 */
void RepoDestroy(VECTOR *vector);
#endif //LAB3_4_REPOSITORY_H
