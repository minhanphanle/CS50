// Implements a dictionary's functionality

#include <cs50.h>
#include <ctype.h>
#include <stdbool.h>
#include "dictionary.h"
#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include <string.h>

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

// TODO: Choose number of buckets in hash table
const unsigned int N = 26;

// Hash table
node *table[N];

// Variables
unsigned int wcount;
unsigned int hash_val;


// Returns true if word is in dictionary, else false
// case insensitive
bool check(const char *word)
{
    // hash the word
    hash_val = hash(word);

    // point a pointer to the bucket at the hash value
    node *pointer = table[hash_val];

    // iterate through the linked list of the bucket

    while (pointer != NULL)
    {
        if (strcasecmp(word, pointer->word) == 0)
        {
            return true;
        }
        pointer = pointer->next;
    }

    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    // TODO: Improve this hash function

    int total = 0;
    for (int i = 0; i < strlen(word); i++)
    {
        total = (53 * total + tolower(word[i])) % N; // multiply by a prime number (53)
    }

    return total;
}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    FILE *file = fopen(dictionary, "r");

    // return null if the file cannot be opened
    if (file == NULL)
    {
        printf("Cannot open %s\n", dictionary);
        return false;
    }

    char word[LENGTH + 1];

    // till reaching the end of the file
    while (fscanf(file, "%s", word) != EOF)
    {
        // allocate memory for new node
        node *n = malloc(sizeof(node));

        // returns false if malloc returns null
        if (n == NULL)
        {
            return false;
        }

        // copy the word in the dictionary to the node in hash table
        strcpy(n->word, word); //strcpy(destination, source)

        // obtain hash values
        hash_val = hash(word);

        // point the new node to the current bucket of the table
        n->next = table[hash_val];

        // point the head bucket to the now current bucket (prepend)
        table[hash_val] = n;
        wcount++;
    }
    fclose(file);
    return true;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    // TODO
    if (wcount > 0)
    {
        return wcount;
    }
    return 0;
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    // TODO

    for (int i = 0; i < N; i++)
    {
        node *ptr_free = table[i];
        while (ptr_free != NULL)
        {
            node *next = ptr_free;
            ptr_free = ptr_free->next; // this has to come before freeing the next pointer, else free both next & ptr
            free(next);
        }

    }
    return true;
}

