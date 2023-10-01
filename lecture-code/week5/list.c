
// Implements a list of numbers with an array of dynamic size

#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    //list of 3
    int *list = malloc(sizeof(int) * 3);
    if (list == NULL)
    {
        return 1;
    }

    //Initialize list of 3
    list[0] = 1;
    list[1] = 2;
    list[2] = 3;

    // printf("sizeof list: %lu\n", sizeof(&list));

    //list of 4
    int *tmp = malloc(sizeof(int) * 4);
    if(tmp == NULL)
    {
        free(list);
        return 1;
    }

    // printf("sizeof list: %lu\n", sizeof(&list));
    // printf("sizeof tmp: %lu\n", sizeof(&tmp));

    for (int i = 0; i < 3; i++)
    {
        tmp[i] = list[i];
    }

    tmp[3] = 4;

    //free list of size 3
    free(list);

    //remember list of size 4
    list = tmp;


    // printf("sizeof list: %lu\n", sizeof(*list));

    for (int i = 0; i < 4; i++)
    {
        printf("list[%i]: %i\n", i, list[i]);
    }

    free(list);

    // Realloc

    //list of 4
    list = malloc(sizeof(int) * 4);
    if (list == NULL)
    {
        return 1;
    }

    list[0] = 1;
    list[1] = 2;
    list[2] = 3;
    list[3] = 4;

    int *tmp1 = realloc(list, sizeof(int) * 5);
    if (tmp1 == NULL)
    {
        free(list);
        return 1;
    }

    list = tmp1;

    list[4] = 5;

    for (int i = 0; i < 5; i++)
    {
        printf("list[%i]: %i\n", i, list[i]);
    }

    free(list);
    return(0);

}