#include <ctype.h>
#include <cs50.h>
#include <stdio.h>
#include <string.h>

// Points assigned to each letter of the alphabet
int POINTS[] = {1, 3, 3, 2, 1, 4, 2, 4, 1, 8, 5, 1, 3, 1, 1, 3, 10, 1, 1, 1, 1, 4, 4, 8, 4, 10};

int compute_score(string word);

int main(void)
{
    // Get input words from both players
    string word1 = get_string("Player 1: ");
    string word2 = get_string("Player 2: ");

    // Score both words
    int score1 = compute_score(word1);
    int score2 = compute_score(word2);

    if (score1 > score2)
    {
        printf("Player 1 wins!\n");
    }
    else if (score1 < score2)
    {
        printf("Player 2 wins!\n");
    }
    else
    {
        printf("Tie!\n");
    }

    //printf("score 1 = %i\n", score1);
    //printf("score 2 = %i\n", score2);

}

int compute_score(string word)
{
    string s = word;
    string letter = "abcdefghijklmnopqrstuvwxyz";
    int score = 0;

    //mapping of the letter in given word

    int index[strlen(s)];

    for (int i = 0, n = strlen(s); i < n; i++)
    {
        if (isupper(s[i]))
        {
            s[i] = s[i] + 32;
        }
        for (int i1 = 0, n1 = strlen(letter); i1 < n1; i1++)
        {
            if (s[i] == letter[i1])
            {
                index[i] = i1;
            }
            else
            {
                index[i] = 27;
            }
            score += POINTS[index[i]];
        }
    }
    return score;
}
