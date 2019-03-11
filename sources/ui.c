//
// Created by Horatiu on 06-Mar-19.
//

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "../headers/ui.h"
#include "../headers/controller.h"


void run(VECTOR *vector)
{
    printf("Happy Holidays!\n");
    printf("Useful commands: add, remove, update, list\n");
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
                printf("%s", ControllerAdd(vector, destination, day, month, year, type, price));
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
                printf("%s", ControllerRemove(vector, destination, day, month, year));
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
                printf("%s", ControllerUpdate(vector, destination, day, month, year, type, price));
            }
            else
                printf("Unrecognized pattern\n");
        }
        else if (strcmp(command, "list") == 0)
        {
            char name[100];
            if (sscanf(line, "%s %s", command, name) == 2 && strcmp(name, "\0") != 0)
            {
                char *output = ControllerList(vector, name);
                printf("%s", output);
                free(output);
            }
            else
            {
                char *output = ControllerList(vector, NULL);
                printf("%s", output);
                free(output);
            }
        }
        else
        {
            printf("Unrecognized pattern\n");
        }

    }
}
