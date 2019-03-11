//
// Created by Horatiu on 06-Mar-19.
//

#ifndef LAB3_4_CONTROLLER_H
#define LAB3_4_CONTROLLER_H

#include "vector.h"

const char *
ControllerAdd(VECTOR *vector, char destination[100], int day, int month, int year, char type[20],
              int price);

const char *
ControllerUpdate(VECTOR *vector, char destination[100], int day, int month, int year, char type[20],
                 int price);

const char *
ControllerRemove(VECTOR *vector, char destination[100], int day, int month, int year);

char *ControllerList(VECTOR *vector, char name[100]);

#endif //LAB3_4_CONTROLLER_H

