// Implements a dictionary's functionality

#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <strings.h>

#include "dictionary.h"

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

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    bool in_dictionary = false;

    int index = hash(word);

    node *list = table[index];

    while (list != NULL)
    {
        if (strcasecmp(list->word, word)  == 0)
        {
            in_dictionary = true;
            break;
        }
        else
            list = list->next;
    }

    return in_dictionary;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    return toupper(word[0]) - 'A';
}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    bool successful = false;
    char the_word[LENGTH + 1];

    // Open dictionary file
    FILE *dict = fopen(dictionary, "r");
    if (dict == NULL)
    {
        printf("Could not open %s.\n", dictionary);
        return EXIT_FAILURE;
    }

    // Read strings from file one at a time
    // fscanf will return EOF once it reaches end of file
    while (fscanf(dict, "%s", the_word) != EOF)
    {
        // Create a new node
        node *the_node = malloc(sizeof(node));

        if (the_node != NULL)
        {
            strcpy(the_node->word, the_word);
            the_node->next = NULL;
        }
        else
        {
            free(the_node);
            return EXIT_FAILURE;
        }

        // hash word
        int index = hash(the_word);

        // Insert the node into hash table
        // empty linked-list
        if (table[index] == NULL)
            table[index] = the_node;

        // non-empty linked-list
        else
        {
            the_node->next = table[index];
            table[index] = the_node;
        }
    }
    successful = true;

    fclose(dict);

    return successful;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    int size = 0;

    for (int i = 0; i < N; i++)
    {
        node *list = table[i];

        while (list != NULL)
        {
            size++;
            list = list->next;
        }
    }

    return size;
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    bool successful = false;

    for (int i = 0; i < N; i++)
    {
        node *list = table[i];

        while (list != NULL)
        {
            node *temp_node = list;
            list = list->next;
            free(temp_node);
        }
    }
    successful = true;

    return successful;
}
