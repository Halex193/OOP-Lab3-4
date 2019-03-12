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


void run(Repository repository)
{
    ControllerPopulate(repository);
    printf("Happy Holidays!\n");
    printf("Our offers are characterized by destination, date, type and price\n");
    printf("Available commands: add, remove, update, list\n");
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
            VECTOR *temporaryList;
            if (sscanf(line, "%s %s", command, name) == 2 && strcmp(name, "\0") != 0)
            {
                temporaryList = ControllerList(repository, name);
            }
            else
            {
                temporaryList = ControllerList(repository, NULL);
            }
            unsigned int listSize = (unsigned int) VecGetCount(temporaryList);
            char *output = (char *) calloc(sizeof(char), listSize * 1024);
            for (int i = 0; i < listSize; i++)
            {
                Offer *listOffer;
                VecGetValueByIndex(temporaryList, i, (void **) &listOffer);
                char buffer[300];
                char *dateString = DateToString(listOffer->departureDate);
                sprintf(buffer, "%s - %s - %s - %d", listOffer->destination,
                        dateString, listOffer->type, listOffer->price);
                free(dateString);
                strcat(output, buffer);
                strcat(output, "\n");
            }
            VecDestroy(&temporaryList);
            printf("%s", output);
            free(output);
        }
        else
        {
            printf("Unrecognized pattern\n");
        }

    }
}
