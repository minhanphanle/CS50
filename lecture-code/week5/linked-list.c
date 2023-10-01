// Prepends numbers to a linked-list, use while or for looop to print

#include <cs50.h>
#include <stdlib.h>
#include <stdio.h>


typedef struct node
{
    int number;
    struct node *next;
}
node;

int main(int argc, char *argv[])
{
    node *list = NULL;

    for (int i = 1; i < argc; i++)
    {
        node *n = malloc(sizeof(node));
        if (n == NULL)
        {
            return 1;
        }

        (*n).number = atoi(argv[i]);
        n->next = NULL;

        // Prepend node to list
        n->next = list;
        list = n;

        // Append
        
    }

    //print memory
    //use while
    node *ptr = list;
    while (ptr != NULL)
    {
        printf("%i\n", ptr->number);
        ptr = ptr->next;
    }

    //use for
    // for (node *ptr = list; ptr != NULL; ptr = ptr->next)
    // {
    //      printf("%i\n", ptr->number);
    // }

    //free memory
    ptr = list;
    while (ptr != NULL)
    {
        list = ptr->next;
        free(ptr);
        ptr = list;
    }

    ///or
    // ptr = list;
    // while (ptr != NULL)
    // {
    //     node *next = ptr->next;
    //     free(ptr);
    //     ptr = next;
    // }
}


