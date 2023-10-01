#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

bool unique(string input_key);
char encrypt(char character, string input_key);

int main(int argc, string argv[])
{
    // check for null
    if ((argv[1] == NULL) || (argc != 2))
    {
        printf("Usage: %s key\n", argv[0]);
        return 1;
    }

    // check for 26 unique alphabets
    int len = strlen(argv[1]);
    int test_unique = unique(argv[1]);

    if (len != 26)
    {
        printf("String has to contain 26 letters!\n");
        return 1;
    }
    else if (test_unique == false)
    {
        printf("String must contain distinct alphabets!\n");
        return 1;
    }
    else
    {
        for (int i = 0; i < len; i++)
        {
            argv[1][i] = tolower(argv[1][i]);
            if (((argv[1][i] - 'a') >= 26) || (('z' - argv[1][i]) >= 26))
            {
                printf("Key has to contain only alphabets!\n");
                return 1;
            }
        }
    }

    string text = get_string("plaintext: ");
    int len_plaintext = strlen(text);
    for (int i = 0; i < len_plaintext; i++)
    {
        text[i] = encrypt(text[i], argv[1]);
    }
    printf("ciphertext: %s", text);

    printf("\n");

    return 0;

}

// check for uniqueness
bool unique(string input_key)
{
    for (int i = 0, k = strlen(input_key); i < k; i++)
    {
        unsigned char x = input_key[i];
        x = tolower(x);
        for (int n = i + 1; n < k; n++)
        {
            unsigned char y = input_key[n];
            y = tolower(y);
            if (x == y)
            {
                return false;
            }
        }
    }
    return true;
}

// encryption
char encrypt(char text, string input_key)
{
    string cap_alphabet = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    string alphabet = "abcdefghijklmnopqrstuvwxyz";
    // string key = tolower_string(input_key);
    // string cap_key = toupper_string(input_key);

    for (int i = 0, k = strlen(input_key); i < k; i++)
    {
        if (text == cap_alphabet[i])
        {
            unsigned char x = input_key[i];
            x = toupper(x);
            text = x;
            return text;
        }
        else if (text == alphabet[i])
        {
            unsigned char y = input_key[i];
            y = tolower(y);
            text = y;
            return text;
        }
    }
    return text;

}

