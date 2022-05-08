#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <math.h>

#define MAX_LENGTH 1000
#define CONST1 0.0588
#define CONST2 0.296
#define CONST3 15.8

//prototypes
int count_sentences(char *text);
int count_letters(char *text);
int count_words(char *text);

int main(void)
{
    char buffer[MAX_LENGTH];

    // getting user's input
    printf("Text: ");
    fgets(buffer, sizeof(buffer), stdin);
    buffer[strlen(buffer) - 1] = '\0';  // replace '\n' to '\0' to terminate input

    int words = count_words(buffer);
    int sentences = count_sentences(buffer);
    int letters = count_letters(buffer);

    float L = (float) letters / words * 100;
    float S = (float) sentences / words * 100;

    // Coleman-Liau index of a text
    int index = round(CONST1 * L - CONST2 * S - CONST3);

    printf("%d letter(s)\n", letters);
    printf("%d sentence(s)\n", sentences);
    printf("%d word(s)\n", words);

    if (index > 16)
        printf("Grade 16+\n");

    else if (index < 1)
        printf("Before Grade 1\n");

    else
        printf("Grade %i\n", index);

}

// helper methods
int count_letters(char *text)
{
    int letters = 0;

    for (int i = 0; i < strlen(text); i++)
        if ((text[i] >= 'a' && text[i] <= 'z') | (text[i] >= 'A' && text[i] <= 'Z'))
            letters += 1;

    return letters;
}

int count_words(char *text)
{
    int words = 0;

    for (int i = 0; i < strlen(text); i++)
        if (text[i] == ' ')
            words += 1;

    return words + 1;
}

int count_sentences(char *text)
{
    int sentences = 0;

    for (int i = 0; i < strlen(text); i++)
        if (text[i] == '.' | text[i] == '?' | text[i] == '!')
            sentences += 1;

    return sentences;
}

