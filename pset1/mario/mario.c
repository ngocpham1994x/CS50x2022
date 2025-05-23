#include <stdio.h>
#include <stdlib.h>

#define MAX_LENGTH 5

char buffer[MAX_LENGTH];
int height;

//prototype
void print_pyramid(int height);

int main(void)
{
    do
    {
        printf("Height: ");
        fgets(buffer, sizeof(buffer), stdin);   // get user input
        height = atoi(buffer);
    }
    while (height <= 0 || height >= 9);          // if outside the bounds, keep asking

    print_pyramid(height);
}

void print_pyramid(int the_height)
{
    for (int line = 1; line <= the_height; line++)
    {
        //print left side of the pyramid
        for (int i = 1; i <= the_height - line; i++)
        {
            printf(" ");
        }
        for (int j = 1; j <= line; j++)
        {
            printf("#");
        }

        //print gap between adjacent pyramids
        printf("  ");

        //print right side of the pyramid
        for (int j = 1; j <= line; j++)
        {
            printf("#");
        }

        //move to new line
        printf("\n");
    }
}
