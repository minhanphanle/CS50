#include <cs50.h>
#include <stdio.h>

int main(void)
{
    int k;
    int row;
    int column;
    int h;

    do
    {
        h = get_int("Height > 1 and < 8: ");
    }
    while (h < 1|| h > 8);
    for (row = 0; row < h; row++)
    {
        k = h - row - 1;
        for (column = 0; column < h; column++)
        {
            if (column >= k)
            {
                printf("#");
            }
            else
            {
                printf(" ");
            }
        }
        printf("  ");
        for (column = 0; column <= row; column++)
        {
            printf("#");
        }
        printf("\n");
    }
}