//
// Created by Horatiu on 06-Mar-19.
//

#include <stddef.h>
#include "../headers/controller.h"
#include "../headers/model.h"

const char *
ControllerAdd(VECTOR *vector, char destination[100], int day, int month, int year, char type[20], int price)
{
    Offer* offer;
    OfferCreate(&offer, destination, day, month, year, type, price);
    return NULL;
}