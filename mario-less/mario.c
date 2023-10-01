#include <cs50.h>
#include <stdio.h>

int main(void)
{
    int n;
    int row;
    int k;
    int column;
    do
    {
        n = get_int("Positive number between 1 and 8: ");
    }
    while (n < 1 || n > 8);
    for (row = 0; row < n; row++)
    {
        k = n - row - 1;
        for (column = 0; column < n; column++)
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
        printf("\n");
    }
}