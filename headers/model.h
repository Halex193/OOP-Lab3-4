//
// Created by Horatiu on 06-Mar-19.
//

#ifndef LAB3_4_MODEL_H
#define LAB3_4_MODEL_H

typedef struct _Date
{
    int day;
    int month;
    int year;
} Date;

typedef struct _Offer
{
    char type[20];
    char destination[100];
    Date departureDate;
    int price;
} Offer;

/**
 * Creates an offer
 * @param offer The pointer to the offer that will be created
 * @param destination The destination of the trip
 * @param day The day of the trip
 * @param month The month of the trip
 * @param year The year of the trip
 * @param type The type of the trip
 * @param price The price of the trip
 */
void OfferCreate(Offer **offer, char destination[100], int day, int month, int year, char type[20], int price);

/**
 * Deallocates the offer struct
 * @param offer THe offer struct to be deallocated
 */
void OfferDestroy(Offer **offer);

/**
 * Checks the equality of two offer structs
 * @return 1 if the offers are equal, otherwise 0
 */
int OfferEquals(Offer *offer1, Offer *offer2);

/**
 * Checks the equality of two date structs
 * @return 1 if the offers are equal, otherwise 0
 */
int DateEquals(Date date1, Date date2);

/**
 * Converts a date struct to its string representation
 * @return 1 if the offers are equal, otherwise 0
 */
char * DateToString(Date date);

int OfferTypeValid(char *type);
#endif //LAB3_4_MODEL_H

