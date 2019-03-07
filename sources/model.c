//
// Created by Horatiu on 06-Mar-19.
//

#include <stdlib.h>
#include <string.h>
#include "../headers/model.h"

void OfferCreate(Offer **offer, char *destination, int day, int month, int year, char *type, int price)
{
    *offer = (Offer *) malloc(sizeof(Offer));
    strcpy((*offer)->destination, destination);
    strcpy((*offer)->destination, type);
    (*offer)->departureDate.day = day;
    (*offer)->departureDate.month = month;
    (*offer)->departureDate.year = year;
    (*offer)->price = price;
}

void OfferDestroy(Offer **offer)
{
    free(*offer);
    *offer = NULL;
}
