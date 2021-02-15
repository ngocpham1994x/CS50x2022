#include <cs50.h>
#include <stdio.h>

//prototype
void printpyramid(int height);

int main(void)
{
    int height;
    do
    {
        height = get_int("Height: ");
    }
    while (0 >= height || height >= 9);
    printpyramid(height);
}

void printpyramid(int height)
{
    for (int line = 1; line <= height; line++)
    {
        //print left side of the pyramid
        for (int i = 1; i <= height - line; i++)
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

        //no need for these commented codes
        // for (int i = 1; i <= height - line; i++)
        // {
        //     printf(" ");
        // }


        //move to new line
        printf("\n");
    }
}
