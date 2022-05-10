#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <math.h>

#define MAX_LENGTH 1000


//prototypes
char** tokenize_by_delimiter(char* string, const char* delimiter);
int count_tokens(char** token_array);
void print_token_arr(char** token_array);


int main(void)
{
    char buffer[MAX_LENGTH];

    printf("Text: ");
    fgets(buffer, sizeof(buffer), stdin);
    buffer[strlen(buffer) - 1] = '\0';  // replace '\n' to '\0' to terminate input


    char** word_array = tokenize_by_delimiter(buffer, " ");  // array of pointers
    int words = count_tokens(word_array);

    printf("words: ==%d==\n", words);
    print_token_arr(word_array);


}

char** tokenize_by_delimiter(char* string, const char* delimiter)
{
  int count = 0;
  char* token = strtok (string, delimiter);
  char** token_array = malloc(strlen(string) * sizeof (char*));

  while (token != NULL)
  {
      token_array[count] = malloc( sizeof(char) );
      token_array[count++] = token;
      token = strtok(NULL, delimiter);
  }

  return token_array;
}

int count_tokens(char** token_array)
{
  int count = 0;

  while (*token_array)
  {
      token_array++;
      count++;
  }

  return count;
}

void print_token_arr(char** token_array)
{
  int count = 0;

  while (*token_array)
  {
    printf("[%s]\n", *token_array++);
    count++;
  }
}
