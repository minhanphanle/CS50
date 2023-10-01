#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>


bool only_digits(string s);
char rotate(char character, int n);

int main(int argc, string argv[])
{
    // check for null
    if (argv[1] == NULL)
    {
        printf("Usage: %s key\n", argv[0]);
        return 1;
    }

    // check for valid key

    bool check = only_digits(argv[1]);

    // printf("bool: %d", check);

    if ((argc != 2) || (check == false))
    {
        printf("Usage: %s key\n", argv[0]);
        return 1;
    }

    int k = atoi(argv[1]);

    // using the key

    string text = get_string("plaintext: ");

    for (int i = 0, t = strlen(text); i < t; i++)
    {
        text[i] = rotate(text[i], k);
    }

    printf("ciphertext: %s\n", text);

}

// check if only digit
bool only_digits(string s)
{
    string str = s;
    for (int i = 0, n = strlen(str); i < n; i++)
    {
        if (((str[i] - '0') < 0) || ((str[i] - '0') > 9))
        {
            return false;
        }
    }
    return true;
}

//Encryption
char rotate(char character, int k)
{
    char c = character;
    int key = k;

    if (isupper(c) != 0)
    {
        c = c - 'A';
        c = (c + key) % 26;
        c += 'A';
    }
    else if (islower(c) != 0)
    {
        c = c - 'a';
        c = (c + key) % 26;
        c += 'a';
    }
    return c;
}
