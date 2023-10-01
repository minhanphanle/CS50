#include <stdio.h>
#include <cs50.h>
#include <string.h>


int main(void)
{
    int n = 50;
    printf("%i\n", n); // 50
    printf("%p\n", &n); // address of n

    int *p = &n;
    printf("%p\n", p); // address of n
    printf("%i\n", *p); // 50

        //String as char *
    string s = "HI!";
    printf("%p\n", s);
    printf("%p\n", &s[0]);
    printf("%p\n", &s[1]);
    printf("%p\n", &s[2]);
    printf("%p\n", &s[3]);

    char *s1 = "HI!";
    printf("%s\n", s1);

        //Pointer arithmetic
    printf("%c\n", s1[0]);
    printf("%c\n", s1[1]);
    printf("%c\n", s1[2]);

    printf("%c\n", *s1);
    printf("%c\n", *(s1+1));
    printf("%c\n", *(s1+2));

        //Compare two string

    //compare memory
    char *s2 = get_string("s2: ");
    char *t = get_string("t: ");

    if (s == t)
    {
        printf("Same\n");
    }
    else
    {
        printf("Different\n");
    }

    printf("%p\n", &s2);
    printf("%p\n", &t);

    //compare the string content

    if (!strcmp(s2, t))
    {
        printf("Same\n");
    }
    else
    {
        printf("Different\n");
    }

    ////

    if (*s2 == *t)
    {
        printf("Same\n");
    }
    else
    {
        printf("Different\n");
    }
}

// & provides the address of n
// * : dereference -> instructs compiler to go to address and take the value


