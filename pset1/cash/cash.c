#include <cs50.h>
#include <stdio.h>
#include <math.h>

int main(void)
{
    //input floating values
    float val;
    do
    {
        val = get_float("Change owed: ");
    }
    while (val <= 0);

    //convert floating values to integer values for precision
    int count = 0;
    int cents = round(val * 100);

    //greedy algorithm
    while (cents >= 25)
    {
        count++;
        cents -= 25;
    }
    while (cents >= 10)
    {
        count++;
        cents -= 10;
    }
    while (cents >= 5)
    {
        count++;
        cents -= 5;
    }
    while (cents >= 1)
    {
        count++;
        cents -= 1;
    }

    //output total coins for change
    printf("%i\n", count);
}