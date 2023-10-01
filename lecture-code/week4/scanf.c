#include <stdio.h>

int main(void)
{
    //integer
    int i;
    printf("i is: ");
    scanf("%i", &i);
    printf("i is: %i\n", i);

    //string (speical case)
        // won't work
        // char *s;
        // printf("s is: ");
        // scanf("%s", s);
        // printf("s is: %s\n", s);

    //work
    char s1[4]; //have to pre-allocate space for array, cannot exceed
    printf("s is: ");
    scanf("%s", s1);
    printf("s is: %s\n", s1);

}