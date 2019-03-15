//
// Created by Horatiu on 06-Mar-19.
//

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "../headers/model.h"

void
OfferCreate(Offer **offer, char *destination, int day, int month, int year, char *type, int price)
{
    *offer = (Offer *) malloc(sizeof(Offer));
    strcpy((*offer)->destination, destination);
    strcpy((*offer)->type, type);
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

Offer *OfferCopy(Offer *offer)
{
    Offer *newOffer;
    OfferCreate(&newOffer, offer->destination, offer->departureDate.day, offer->departureDate.month,
                offer->departureDate.year, offer->type, offer->price);
    return newOffer;
}

int OfferEquals(Offer *offer1, Offer *offer2)
{
    return strcmp(offer1->destination, offer2->destination) == 0 &&
           DateEquals(offer1->departureDate, offer2->departureDate);
}

int DateEquals(Date date1, Date date2)
{
    return date1.day == date2.day &&
           date1.month == date2.month &&
           date1.year == date2.year;
}

char *DateToString(Date date)
{
    char *dateString = (char *) malloc(sizeof(char) * 11);
    sprintf(dateString, "%d.%d.%d", date.day, date.month, date.year);
    return dateString;
}

int OfferTypeValid(char *type)
{
    return strcmp(type, "seaside") == 0 ||
           strcmp(type, "mountain") == 0 ||
           strcmp(type, "city-break") == 0;
}

int DateGreater(Date date1, Date date2)
{
    if (date1.year > date2.year)
    {
        return 1;
    }
    if (date1.year == date2.year)
    {
        if (date1.month > date2.month)
        {
            return 1;
        }
        if (date1.month == date2.month)
        {
            if (date1.day >= date2.day)
            {
                return 1;
            }
            return 0;
        }
        return 0;
    }
    return 0;
}
