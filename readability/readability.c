#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

//function prototype
int count_letters(string text);
int count_words(string text);
int count_sentences(string text);

int main(void)
{
    string text = get_string("Text: ");
    int letters = count_letters(text);
    int words = count_words(text);
    int sentences = count_sentences(text);

// index calculations
    float L = ((float) letters) / ((float) words) * 100;
    float S = ((float) sentences) / ((float) words) * 100;
    int index = round(0.0588 * L - 0.296 * S - 15.8);

    // printf("%f L\n", L);
    // printf("%f S\n", S);
    // printf("%i letters\n", letters);
    // printf("%i words\n", words);
    // printf("%i sentences\n", sentences);

    if (index >= 16)
    {
        printf("Grade 16+\n");
    }
    else if (index < 1)
    {
        printf("Before Grade 1\n");
    }
    else
    {
        printf("Grade %i\n", index);
    }
}

// count letters
int count_letters(string text)
{
    string s = text;
    int letters = 0;
    for (int i = 0, n = strlen(s); i < n; i++)
    {
        switch (s[i])
        {
            case 'A' ... 'Z':
                letters += 1;
                break;
            case 'a' ... 'z':
                letters += 1;
                break;
        }
    }
    return letters;
}

// count words
int count_words(string text)
{
    string s = text;
    int words = 0;
    for (int i = 0, n = strlen(s); i < n; i++)
    {
        if (s[i] == ' ')
        {
            words += 1;
        }
    }

    return words += 1;
}

// count sentences
int count_sentences(string text)
{
    string s = text;
    int sentences = 0;
    for (int i = 0, n = strlen(s); i < n; i++)
    {
        if ((s[i] == '.') || (s[i] == '!') || (s[i] == '?'))
        {
            sentences += 1;
        }
    }
    return sentences;
}



