//
// Created by Horatiu on 06-Mar-19.
//

#ifndef LAB3_4_CONTROLLER_H
#define LAB3_4_CONTROLLER_H

#include "vector.h"
#include "repository.h"
#include "model.h"

/**
 * Adds an offer to the repository
 * @param vector The vector that contains the stored offers
 * @param destination The destination of the trip
 * @param day The day of the trip
 * @param month The month of the trip
 * @param year The year of the trip
 * @param type The type of the trip
 * @param price The price of the trip
 * @return A message for the user indicating the result of the operation
 */
const char *
ControllerAdd(Repository vector, char *destination, int day, int month, int year, char *type,
              int price);

/**
 * Updates an offer of the repository
 * @param repository The repository that contains the stored offers
 * @param destination The destination of the trip
 * @param day The day of the trip
 * @param month The month of the trip
 * @param year The year of the trip
 * @param type The type of the trip
 * @param price The price of the trip
 * @return A message for the user indicating the result of the operation
 */
const char *
ControllerUpdate(Repository repository, char destination[100], int day, int month, int year, char type[20],
                 int price);

/**
 * Removed an offer of the repository
 * @param repository The repository that contains the stored offers
 * @param destination The destination of the trip
 * @param day The day of the trip
 * @param month The month of the trip
 * @param year The year of the trip
 * @return A message for the user indicating the result of the operation
 */
const char *
ControllerRemove(Repository repository, char destination[100], int day, int month, int year);

/**
 * Lists the filtered offers of the repository
 * @param searchString The string to be found in the destination. If the parameter is NULL, no filtering is applied
 * @return A message for the user indicating the result of the operation (the memory needs to be freed afterwards)
 */
VECTOR *ControllerList(Repository repository, char searchString[100]);

VECTOR *ControllerListYear(Repository repository, int year);

/**
 * Populates the repository with default data
 * @param repository The repository that contains the stored offers
 */
void ControllerPopulate(Repository repository);

/**
 * Function for the in-lab activity
 */
VECTOR *ControllerBonus(Repository repository, char* destination);

VECTOR *ControllerListType(Repository repository, char type[20], Date date)
#endif //LAB3_4_CONTROLLER_H

