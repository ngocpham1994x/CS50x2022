#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <math.h>

#define MAX_LENGTH 1000
#define ALPHABET_CHARS 26

//prototype
bool is_valid(char* key);
char* check_caesar(char* plaintext, int key);


int main(int argc, char* argv[])
{
    if (argc < 2 || argc > 2)
    {
        fprintf(stderr, "Usage: ./caesar key\n");
        exit(EXIT_FAILURE);
    }
    else if (!is_valid(argv[1]))
    {
        fprintf(stderr, "Key is invalid.\n");
        exit(EXIT_FAILURE);
    }

    int key = atoi(argv[1]);

    char plaintext[MAX_LENGTH];
    char* ciphertext;

    printf("plaintext: ");
    fgets(plaintext, sizeof(plaintext), stdin);

    ciphertext = check_caesar(plaintext, key);
    printf("ciphertext: %s\n", ciphertext);

    return EXIT_SUCCESS;
}

bool is_valid(char* key)
{
    bool valid = true;

    for (int i = 0; i < strlen(key); i++)
    {
        if (key[i] < '0' || key[i] > '9')
        {
            valid = false;
            break;
        }
    }

    return valid;
}

char* check_caesar(char* plaintext, int key)
{
    //this works, but recommend to use string copy functions
    char* ciphertext = plaintext;

    int shift_key = key % 26;

    //actual shifting key is the remainder of division,
    // loop around 26 chars x (times) is the same as one (time) and stop at desired char.
    for (int i = 0; i < strlen(plaintext); i++)
    {
        // the char is in either of 2 groups
        if( (plaintext[i] >= 'a' && plaintext[i] <= 'z') || (plaintext[i] >= 'A' && plaintext[i] <= 'Z') )
        {
            int replacement = plaintext[i] + shift_key;

            if (((plaintext[i] >= 'a' && plaintext[i] <= 'z') && (replacement > 'z')) | ((plaintext[i] >= 'A' && plaintext[i] <= 'Z')
                    && (replacement > 'Z')))
                // return (aka loop back) if at the end of letter in alphabet: 'z' or 'Z'
                ciphertext[i] = (char)(replacement - 26);

            else
                ciphertext[i] = (char)(replacement);
        }
        else //if char is not an alphabet
            ciphertext[i] = (char)(plaintext[i]);
    }

    return ciphertext;
}