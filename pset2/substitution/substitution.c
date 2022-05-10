#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#define MAX_LENGTH 1000
#define ALPHABET_CHARS 26

//prototypes
bool is_valid(char* key);
bool is_uppercase(char c);
bool is_lowercase(char c);
char to_uppercase(char c);
char to_lowercase(char c);
char* encrypt(char* plaintext, char* key);

int main(int argc, char *argv[])
{
    if (argc < 2 || argc > 2)
    {
        fprintf(stderr, "Usage: ./substitution key\n");
        exit(EXIT_FAILURE);
    }
    else if (strlen(argv[1]) < 26)
    {
        fprintf(stderr, "Key must contain 26 characters.\n");
        exit(EXIT_FAILURE);
    }
    else if (!is_valid(argv[1]))
    {
        fprintf(stderr, "Key is invalid.\n");
        exit(EXIT_FAILURE);
    }

    char* key = argv[1];
    char plaintext[MAX_LENGTH];
    char* ciphertext;

    printf("plaintext: ");
    fgets(plaintext, sizeof(plaintext), stdin);


    ciphertext = encrypt(plaintext, key);

    printf("ciphertext: %s\n", ciphertext);

    free(ciphertext);

    return EXIT_SUCCESS;
}

bool is_valid(char* key)
{
    bool valid = true;
    int frequency[ALPHABET_CHARS] = {0};

    char uppercase_key[strlen(key)];
    strcpy(uppercase_key, key);

    // convert key to uppercase
    for (int i = 0; i < strlen(key); i++)
        uppercase_key[i] = to_uppercase(key[i]);

    // handles invalid characters in key
    for (int i = 0; i < strlen(key); i++)
    {
        if (uppercase_key[i] < 'A' || uppercase_key[i] > 'Z')
        {
            valid = false;
            break;
        }
        else
            frequency[uppercase_key[i] - 'A'] += 1;
    }

    // handles multiple duplicate characters in key
    for (int i = 0; i < ALPHABET_CHARS; i++)
    {
        if (frequency[i] > 1)
        {
            valid = false;
            break;
        }
    }

    return valid;
}

bool is_uppercase(char c)
{
    bool is_uppercase = false;

    if (c >= 'A' && c <= 'Z')
        is_uppercase = true;

    return is_uppercase;
}

bool is_lowercase(char c)
{
    bool is_lowercase = false;

    if (c >= 'a' && c <= 'z')
        is_lowercase = true;

    return is_lowercase;
}

char to_uppercase(char c)
{
    char new_c = c;

    if (is_lowercase(c))
        new_c -= 32;

    return new_c;
}

char to_lowercase(char c)
{
    char new_c = c;

    if (is_uppercase(c))
        new_c += 32;

    return new_c;
}

char* encrypt(char* plaintext, char* key)
{
    char* ciphertext = malloc(strlen(plaintext) * sizeof (char));

    char uppercase_key[strlen(key)];
    strcpy(uppercase_key, key);

    char lowercase_key[strlen(key)];
    strcpy(lowercase_key, key);

    // convert key to uppercase
    for (int i = 0; i < strlen(key); i++)
        uppercase_key[i] = to_uppercase(key[i]);

    // convert key to lowerkey
    for (int i = 0; i < strlen(key); i++)
        lowercase_key[i] = to_lowercase(key[i]);

    // encrypting
    for (int i = 0; i < strlen(plaintext); i++)
    {
        if (plaintext[i] >= 'A' && plaintext[i] <= 'Z')
        {
            int uppercase_index = plaintext[i] - 'A';
            ciphertext[i] = uppercase_key[uppercase_index];
        }
        else if (plaintext[i] >= 'a' && plaintext[i] <= 'z')
        {
            int lowercase_index = plaintext[i] - 'a';
            ciphertext[i] = lowercase_key[lowercase_index];
        }
        else
            ciphertext[i] = plaintext[i];
    }

    return ciphertext;
}
