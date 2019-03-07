/*
 * Udrea Horațiu 917
 *
 * 3. Tourism Agency
 */

#include <stdio.h>
#include "../headers/vector.h"
#include "../headers/ui.h"
#include "../headers/model.h"

int main()
{
    setbuf(stdout, 0);
    VECTOR *vector;
    VecCreate(&vector);
    run(vector);
    for (int i = 0; i < VecGetCount(vector); i++)
    {
        Offer *offer = NULL;
        VecGetValueByIndex(vector, i, (void *) offer);
        OfferDestroy(&offer);
    }
    VecDestroy(&vector);
    return 0;
}