#include <ctype.h>
#include <cs50.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

int main()
{
    // string s = get_string("s: ");
    // string k = s;

    // if (strlen(k) > 0) // to prevent segmentation core dump due to empty string
    // {
    //     k[0] = toupper(k[0]);
    // }

    // printf("s: %s\n", s);
    // printf("k: %s\n", k);

    ///modify to

    char *s = get_string("s: ");
    char *t = malloc(strlen(s) + 1); //allow for null \0

    // for (int i = 0; i <= strlen(s); i++)
    // {
    //     t[i] = s[i];
    // }

    ///modify to
    for (int i = 0, n = strlen(s); i <= n; i++)
    {
        t[i] = s[i];
    }

    //could use strcpy()

    t[0] = toupper(t[0]);

    printf("s: %s\n", s);
    printf("t: %s\n", t);

    //both get_string and malloc return NULL (special value in memory)
    //in the event something goes wrong -> check4 NULL, return 1
    //free memory at the end, return 0

    // char *s = get_string("s: ");
    // if (s == NULL)
    // {
    //     return 1;
    // }

    // // Allocate memory for another string
    // char *t = malloc(strlen(s) + 1);
    // if (t == NULL)
    // {
    //     return 1;
    // }

    // // Copy string into memory
    // strcpy(t, s);

    // // Capitalize copy
    // if (strlen(t) > 0)
    // {
    //     t[0] = toupper(t[0]);
    // }

    // // Print strings
    // printf("s: %s\n", s);
    // printf("t: %s\n", t);

    // // Free memory
    // free(t);
    // return 0;


}