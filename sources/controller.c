//
// Created by Horatiu on 06-Mar-19.
//

#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "../headers/controller.h"
#include "../headers/model.h"

const char *
ControllerAdd(VECTOR *vector, char destination[100], int day, int month, int year, char type[20],
              int price)
{
    Offer *offer;
    OfferCreate(&offer, destination, day, month, year, type, price);
    for (int i = 0; i < VecGetCount(vector); i++)
    {
        Offer *storedOffer;
        VecGetValueByIndex(vector, i, (void **) &storedOffer);
        if (OfferEquals(offer, storedOffer))
        {
            OfferDestroy(&offer);
            return "Offer already exists!\n";
        }
    }
    VecInsertTail(vector, offer);
    return "Offer was added\n";
}

char *ControllerList(VECTOR *vector, char *name)
{
    char *output = (char *) calloc(sizeof(char), 1024);
    for (int i = 0; i < VecGetCount(vector); i++)
    {
        Offer *storedOffer;
        VecGetValueByIndex(vector, i, (void **) &storedOffer);
        if (name == NULL || strstr(storedOffer->destination, name) != NULL)
        {
            char buffer[300];
            char *dateString = DateToString(storedOffer->departureDate);
            sprintf(buffer, "%s - %s - %s - %d", storedOffer->destination,
                    dateString, storedOffer->type, storedOffer->price);
            free(dateString);
            strcat(output, buffer);
            strcat(output, "\n");
        }
    }
    return output;
}

const char *
ControllerUpdate(VECTOR *vector, char *destination, int day, int month, int year, char *type,
                 int price)
{
    Offer *offer;
    OfferCreate(&offer, destination, day, month, year, type, price);
    for (int i = 0; i < VecGetCount(vector); i++)
    {
        Offer *storedOffer;
        VecGetValueByIndex(vector, i, (void **) &storedOffer);
        if (OfferEquals(offer, storedOffer))
        {
            VecRemoveByIndex(vector, i);
            OfferDestroy(&storedOffer);
            VecInsertTail(vector, offer);
            return "Offer updated!\n";
        }
    }
    OfferDestroy(&offer);
    return "Offer was not found\n";
}

const char *ControllerRemove(VECTOR *vector, char *destination, int day, int month, int year)
{
    Offer *offer;
    OfferCreate(&offer, destination, day, month, year, "", 0);
    for (int i = 0; i < VecGetCount(vector); i++)
    {
        Offer *storedOffer;
        VecGetValueByIndex(vector, i, (void **) &storedOffer);
        if (OfferEquals(offer, storedOffer))
        {
            VecRemoveByIndex(vector, i);
            OfferDestroy(&storedOffer);
            OfferDestroy(&offer);
            return "Offer removed!\n";
        }
    }
    OfferDestroy(&offer);
    return "Offer was not found\n";
}
