#include <stdio.h>

#define MAX_LENGTH 100

char buffer[MAX_LENGTH];   // storing name as buffer

int main(void)
{
    printf("What's your name?\n");

    fgets(buffer, sizeof(buffer), stdin);   // get user input

    printf("hello, %s \n", buffer);
}
