//
// Created by Horatiu on 06-Mar-19.
//

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "../headers/ui.h"
#include "../headers/controller.h"
#include "../headers/repository.h"
#include "../headers/model.h"

void listOffers(VECTOR **offers);

void run(Repository repository)
{
    ControllerPopulate(repository);
    printf("Happy Holidays!\n");
    printf("Our offers are characterized by destination, date, type and price\n");
    printf("Available commands: add, remove, update, list, type\n");
    while (1)
    {
        char command[10];
        printf("> ");
        char line[1024];
        fgets(line, 1024, stdin);
        sscanf(line, "%s", command);
        if (strcmp(command, "exit") == 0)
            break;
        if (strcmp(command, "add") == 0)
        {
            char destination[100];
            int day;
            int month;
            int year;
            char type[20];
            int price;
            if (sscanf(line, "%s %s %d.%d.%d %s %d", command, destination, &day, &month, &year, type, &price) == 7)
            {
                if (!OfferTypeValid(type))
                {
                    printf("Offer type invalid!\n");
                }
                else
                {
                    printf("%s", ControllerAdd(repository, destination, day, month, year, type, price));
                }
            }
            else
                printf("Unrecognized pattern\n");
        }
        else if (strcmp(command, "remove") == 0)
        {
            char destination[100];
            int day;
            int month;
            int year;
            if (sscanf(line, "%s %s %d.%d.%d", command, destination, &day, &month, &year) == 5)
            {
                printf("%s", ControllerRemove(repository, destination, day, month, year));
            }
            else
                printf("Unrecognized pattern\n");
        }
        else if (strcmp(command, "update") == 0)
        {
            char destination[100];
            int day;
            int month;
            int year;
            char type[20];
            int price;
            if (sscanf(line, "%s %s %d.%d.%d %s %d", command, destination, &day, &month, &year, type, &price) == 7)
            {
                if (!OfferTypeValid(type))
                {
                    printf("Offer type invalid!\n");
                }
                else
                {
                    printf("%s", ControllerUpdate(repository, destination, day, month, year, type, price));
                }
            }
            else
                printf("Unrecognized pattern\n");
        }
        else if (strcmp(command, "list") == 0)
        {
            char name[100];
            int year;
            VECTOR *offerList;
            if (sscanf(line, "%s %d", command, &year) == 2)
            {
                offerList = ControllerListYear(repository, year);
            }
            else if (sscanf(line, "%s %s", command, name) == 2 && strcmp(name, "\0") != 0)
            {
                offerList = ControllerList(repository, name);
            }
            else
            {
                offerList = ControllerList(repository, NULL);
            }
            listOffers(&offerList);
        }
        else if (strcmp(command, "bonus") == 0)
        {
            char destination[100];
            if (sscanf(line, "%s %s", command, destination) == 2 && strcmp(destination, "\0") != 0)
            {
                VECTOR *offerList = ControllerBonus(repository, destination);
                listOffers(&offerList);
            }
            else
            {
                printf("Unrecognized pattern\n");
            }

        }
        else if (strcmp(command, "type") == 0)
        {
            Date date;
            char type[20];
            char order[11];
            if (sscanf(line, "%s %s %d.%d.%d %s", command, type, &date.day, &date.month, &date.year, order) == 6)
            {
                if (!OfferTypeValid(type))
                {
                    printf("Offer type invalid!\n");
                }
                else
                {
                    int orderInt = -1;
                    if (strcmp(order, "asc") == 0 || strcmp(order, "ascending") == 0)
                    {
                        orderInt = 1;
                    }
                    else if (strcmp(order, "desc") == 0 || strcmp(order, "descending") == 0)
                    {
                        orderInt = 0;
                    }
                    else
                    {
                        printf("Invalid ordering type!\n");
                    }
                    if (orderInt != -1)
                    {
                        VECTOR *offerList = ControllerListType(repository, type, date, orderInt);
                        listOffers(&offerList);
                    }
                }
            }
            else
            {
                printf("Unrecognized pattern\n");
            }
        }
        else
        {
            printf("Unrecognized pattern\n");
        }

    }
}

void listOffers(VECTOR **offers)
{
    unsigned int listSize = (unsigned int) VecGetCount((*offers));
    if (listSize == 0)
    {
        printf("Nothing to display\n");
        VecDestroy(offers);
        return;
    }
    char *output = (char *) calloc(sizeof(char), listSize * 1024);
    for (int i = 0; i < listSize; i++)
    {
        Offer *listOffer;
        VecGetValueByIndex((*offers), i, (void **) &listOffer);
        char buffer[300];
        char *dateString = DateToString(listOffer->departureDate);
        sprintf(buffer, "%s - %s - %s - %d", listOffer->destination,
                dateString, listOffer->type, listOffer->price);
        free(dateString);
        strcat(output, buffer);
        strcat(output, "\n");
    }
    VecDestroy(offers);
    printf("%s", output);
    free(output);
}
