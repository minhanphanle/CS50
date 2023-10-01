#include <cs50.h>
#include <stdio.h>

int main(void)
{
    int h;
    int i;
    int k;
    int j;
    int t;
    int g;
    do
    {
        h = get_int("Height: ");
    }
    while (h < 1 || h > 8);
    for (i = 0; i < h; i++)
    {
        for (j = 0; j < h - 1 - i; j++)
        {
            printf(" ");
        }
        for (k = h - 1; k >= j; k--)
        {
            printf("#");
        }
        printf("  ");

        for (j = 0; j <= i; j++)
        {
            printf("#");
        }
        printf("\n");
    }
}