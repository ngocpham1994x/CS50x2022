#include <stdio.h>
#include <stdlib.h>
#include <cs50.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

//prototype
bool is_valid(string key);
string caesar_encrypt(string plaintext, int key);


int main(int argc, string argv[])
{
    if (argc == 2)
    {
        string key_in_string = argv[1];
        bool validity = is_valid(key_in_string);

        if (validity)
        {
            int key_in_int = atoi(key_in_string);
            string plaintext = get_string("plaintext: ");
            string ciphertext = caesar_encrypt(plaintext, key_in_int);
            printf("ciphertext: %s\n", ciphertext);
        }
        else
        {
            printf("Usage: ./caesar key");
            return 1;
        }
    }
    else
    {
        printf("No argument or more than two arguments!");
        return 1;
    }
}

bool is_valid(string key)
{
    bool validity = true;
    for (int i = 0, n = strlen(key); i < n; i++)
    {
        if isdigit(key[i]) //(key[i] >= '0' | key[i] <= '9')
        {
            continue;
        }
        else
        {
            validity = false;
            printf("Usage: ./caesar key");
            break;
        }
    }

    return validity;
}

string caesar_encrypt(string plaintext, int key)
{
    string ciphertext = plaintext; //this works, but recommend to use string copy functions

    int shift_key = key % 26;
    //actual shifting key is the remainder of division, loop around 26 chars x (times) is the same as one (time) and stop at desired char.
    for (int i = 0, n = strlen(plaintext); i < n; i++)
    {
        if isalpha(plaintext[i])
            //((plaintext[i] >= 'a' && plaintext[i] <= 'z') | (plaintext[i] >= 'A' && plaintext[i] <= 'Z')) // the char is in either of 2 groups
        {
            int replacement = plaintext[i] + shift_key;
            if (((plaintext[i] >= 'a' && plaintext[i] <= 'z') && (replacement > 'z')) | ((plaintext[i] >= 'A' && plaintext[i] <= 'Z')
                    && (replacement > 'Z')))
            {
                ciphertext[i] = (char)(replacement - 26);  // return (aka loop back) if at the end of letter in alphabet: 'z' or 'Z'
            }
            else
            {
                ciphertext[i] = (char)(replacement);
            }
        }
        else //if char is not an alphabet
        {
            ciphertext[i] = (char)(plaintext[i]);
        }
    }

    return ciphertext;
}