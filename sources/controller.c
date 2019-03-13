//
// Created by Horatiu on 06-Mar-19.
//

#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "../headers/controller.h"
#include "../headers/model.h"

VECTOR *ControllerFilter(VECTOR *offers, void *parameter, int (*valid)(Offer *offer, void *parameter));

const char *
ControllerAdd(Repository repository, char *destination, int day, int month, int year, char *type,
              int price)
{
    VECTOR *offers = repository.offers;
    Offer *offer;
    OfferCreate(&offer, destination, day, month, year, type, price);
    for (int i = 0; i < VecGetCount(offers); i++)
    {
        Offer *storedOffer;
        VecGetValueByIndex(offers, i, (void **) &storedOffer);
        if (OfferEquals(offer, storedOffer))
        {
            OfferDestroy(&offer);
            return "Offer already exists!\n";
        }
    }
    VecInsertTail(offers, offer);
    return "Offer was added\n";
}

int sortByPrice(void *offer1, void *offer2)
{
    return ((Offer *) offer1)->price - ((Offer *) offer2)->price;
}

VECTOR *ControllerList(Repository repository, char *searchString)
{
    VECTOR *offers = repository.offers;
    VECTOR *temporaryList;
    VecCreate(&temporaryList);
    for (int i = 0; i < VecGetCount(offers); i++)
    {
        Offer *storedOffer;
        VecGetValueByIndex(offers, i, (void **) &storedOffer);
        if (searchString == NULL || strstr(storedOffer->destination, searchString) != NULL)
        {
            VecInsertTail(temporaryList, storedOffer);
        }
    }
    VecSort(temporaryList, &sortByPrice);
    return temporaryList;
}

const char *
ControllerUpdate(Repository repository, char *destination, int day, int month, int year, char *type,
                 int price)
{
    VECTOR *offers = repository.offers;
    Offer *offer;
    OfferCreate(&offer, destination, day, month, year, type, price);
    for (int i = 0; i < VecGetCount(offers); i++)
    {
        Offer *storedOffer;
        VecGetValueByIndex(offers, i, (void **) &storedOffer);
        if (OfferEquals(offer, storedOffer))
        {
            VecRemoveByIndex(offers, i);
            OfferDestroy(&storedOffer);
            VecInsertTail(offers, offer);
            return "Offer updated!\n";
        }
    }
    OfferDestroy(&offer);
    return "Offer was not found\n";
}

const char *ControllerRemove(Repository repository, char *destination, int day, int month, int year)
{
    VECTOR *offers = repository.offers;
    Offer *offer;
    OfferCreate(&offer, destination, day, month, year, "", 0);
    for (int i = 0; i < VecGetCount(offers); i++)
    {
        Offer *storedOffer;
        VecGetValueByIndex(offers, i, (void **) &storedOffer);
        if (OfferEquals(offer, storedOffer))
        {
            VecRemoveByIndex(offers, i);
            OfferDestroy(&storedOffer);
            OfferDestroy(&offer);
            return "Offer removed!\n";
        }
    }
    OfferDestroy(&offer);
    return "Offer was not found\n";
}

void ControllerPopulate(Repository repository)
{
    ControllerAdd(repository, "Romania", 12, 12, 2015, "seaside", 16000);
    ControllerAdd(repository, "Chad", 11, 12, 2016, "mountain", 1200);
    ControllerAdd(repository, "Bulgaria", 10, 12, 2013, "city break", 13000);
    ControllerAdd(repository, "Denmark", 9, 6, 2015, "mountain", 19000);
    ControllerAdd(repository, "Syria", 8, 12, 2014, "seaside", 30000);
    ControllerAdd(repository, "Germany", 3, 5, 2016, "city break", 6000);
    ControllerAdd(repository, "France", 5, 3, 2017, "mountain", 4000);
    ControllerAdd(repository, "USA", 23, 5, 2015, "city break", 11000);
    ControllerAdd(repository, "Canada", 15, 2, 2016, "city break", 10000);
    ControllerAdd(repository, "Kenya", 12, 12, 2013, "seaside", 22000);
}

int sortByMonth(void *offer1, void *offer2)
{
    return ((Offer *) offer1)->departureDate.month - ((Offer *) offer2)->departureDate.month;
}

VECTOR *ControllerBonus(Repository repository, char *destination)
{
    VECTOR *offers = repository.offers;
    VECTOR *temporaryList;
    VecCreate(&temporaryList);
    for (int i = 0; i < VecGetCount(offers); i++)
    {
        Offer *storedOffer;
        VecGetValueByIndex(offers, i, (void **) &storedOffer);
        if (strcmp(storedOffer->destination, destination) == 0)
        {
            VecInsertTail(temporaryList, storedOffer);
        }
    }
    VecSort(temporaryList, &sortByMonth);
    return temporaryList;
}
int sameType(Offer *offer, void *year)
{
    return offer->departureDate.year == *((int*)year);
}
VECTOR *ControllerListYear(Repository repository, int year)
{
    VECTOR *temporaryList = ControllerFilter(repository.offers, &year, &sameType);
    VecSort(temporaryList, &sortByPrice);
    return temporaryList;
}

VECTOR *ControllerFilter(VECTOR *offers, void *parameter, int (*valid)(Offer *offer, void *parameter))
{
    VECTOR *temporaryList;
    VecCreate(&temporaryList);
    for (int i = 0; i < VecGetCount(offers); i++)
    {
        Offer *storedOffer;
        VecGetValueByIndex(offers, i, (void **) &storedOffer);
        if (valid(storedOffer, parameter))
        {
            VecInsertTail(temporaryList, storedOffer);
        }
    }
    return temporaryList;
}

VECTOR *ControllerListType(Repository repository, char *type, Date date)
{
    return NULL;
}
