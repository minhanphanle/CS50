#include <stdio.h>
#include <stdlib.h>

void swap(int *a, int *b);

int main(void)
{
    int x = 1;
    int y = 2;

    printf("Before: x is %i, y is %i\n", x, y);

    swap(&x, &y);

    printf("After: x is %i, y is %i\n", x, y);

}

void swap(int *a, int*b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}
