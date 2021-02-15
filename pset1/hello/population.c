#include <cs50.h>
#include <stdio.h>

int main(void)
{
    // TODO: Prompt for start size
    int start_size;
    do
    {
        start_size = get_int("Start size?\n");
    }
    while(start_size<9);


    // TODO: Prompt for end size
    int end_size;
    do
    {
        end_size = get_int("End size?\n");
    }
    while(end_size<start_size);

    // TODO: Calculate number of years until we reach threshold
    int years=0;
    int curr_end_size;

    if(start_size == end_size)
    {
        years = 0;
    }

    else
    {
        do
        {
            curr_end_size = start_size + (start_size/3) - (start_size/4);
            start_size = curr_end_size;
            years++;
        }
        while(curr_end_size < end_size);
    }


    // TODO: Print number of years
    printf("Years: %i \n",years);

}