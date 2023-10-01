#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    int *x = malloc(3 * sizeof(int));
    printf("%lu\n", sizeof(x));
    x[1] = 72;
    x[2] = 73;
    x[3] = 33;
    free(x);
    printf("%lu\n", sizeof(x));
    for(int i = 0; i < sizeof(x); i++)
    {
        printf("%i\n", x[i]);
    }
}