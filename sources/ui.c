//
// Created by Horatiu on 06-Mar-19.
//

#include <stdio.h>
#include <string.h>
#include "../headers/ui.h"
#include "../headers/controller.h"


void run(VECTOR *vector)
{
    printf("Happy Holidays!\n");
    printf("Useful commands: add, remove, update, search\n");
    while (1)
    {
        char command[10];
        printf("> ");
        scanf("%s", command);
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
            if (scanf("%s %d.%d.%d %s %d", destination, &day, &month, &year, type, &price) == 6)
            {
                printf("%s", ControllerAdd(vector, destination, day, month, year, type, price));
                return;
            }
            printf("Unrecognized pattern");
        }
        else if(strcmp(command, "remove") == 0)
        {

        }
        else if(strcmp(command, "update") == 0)
        {

        }
        else if(strcmp(command, "search") == 0)
        {

        }

    }
}
