#include <ctype.h>
// #include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#define MAX_LENGTH 100
char word1[MAX_LENGTH];
char word2[MAX_LENGTH];


// Points assigned to each letter of the alphabet
int POINTS[] = {1, 3, 3, 2, 1, 4, 2, 4, 1, 8, 5, 1, 3, 1, 1, 3, 10, 1, 1, 1, 1, 4, 4, 8, 4, 10};

// prototypes
int compute_score(char *word, size_t length);
bool is_uppercase(char c);
bool is_lowercase(char c);
char to_uppercase(char c);

int main(void)
{
    // Get input words from both players
    printf("Player 1: ");
    fgets(word1, sizeof(word1), stdin);

    printf("Player 2: ");
    fgets(word2, sizeof(word2), stdin);


    // Score both words
    int score1 = compute_score(&word1[0], strlen(word1));
    int score2 = compute_score(&word2[0], strlen(word2));

    // this also works. Pass string as first-char pointer
    // int score1 = compute_score(word1, strlen(word1));
    // int score2 = compute_score(word2, strlen(word2));

    // Print the winner
    if (score1 < score2)
        printf("Player 2 wins!\n");
    else if (score1 > score2)
        printf("Player 1 wins!\n");
    else
        printf("Tie!\n");
}

int compute_score(char *word, size_t length)
{
    int score = 0;

    char local_word[length - 1];
    strcpy(local_word, word);

    // Compute and return score for string

    for (int i = 0; i <= length - 1; i++)
    {
        char c = to_uppercase(local_word[i]);

        if (is_uppercase(c))
        {
            int position = c - 'A';
            score += POINTS[position];
        }
    }

    return score;
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

// below solution uses <cs50.h> library & is graded: 100%

// #include <ctype.h>
// #include <cs50.h>
// #include <stdio.h>
// #include <string.h>

// // Points assigned to each letter of the alphabet
// int POINTS[] = {1, 3, 3, 2, 1, 4, 2, 4, 1, 8, 5, 1, 3, 1, 1, 3, 10, 1, 1, 1, 1, 4, 4, 8, 4, 10};

// // prototype
// int compute_score(string word);

// int main(void)
// {
//     // Get input words from both players
//     string word1 = get_string("Player 1: ");
//     string word2 = get_string("Player 2: ");

//     // Score both words
//     int score1 = compute_score(word1);
//     int score2 = compute_score(word2);

//     // Print the winner
//     if (score1 < score2)
//     {
//         printf("Player 2 wins!");
//     }
//     else if (score1 > score2)
//     {
//         printf("Player 1 wins!");
//     }
//     else
//     {
//         printf("Tie!");
//     }
// }

// int compute_score(string word)
// {
//     int sum = 0;
//     for (int i = 0, n = strlen(word); i < n; i++)
//     {
//         char c = toupper(word[i]);
//         if (isupper(c))
//         {
//             int position = c - 'A';
//             sum += POINTS[position];
//         }
//         else
//         {
//             sum += 0;
//         }
//     }
//     return sum;
// }
