#include <cs50.h>   // did not use cs50 library
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdbool.h>

#define MAX_LENGTH 100

char buffer[MAX_LENGTH];
char* pointer;
float val;

//prototype
bool is_contain_char(char* the_buffer);

int get_cents(void);
int calculate_quarters(int cents);
int calculate_dimes(int cents);
int calculate_nickels(int cents);
int calculate_pennies(int cents);

int main(void)
{
    // Ask how many cents the customer is owed
    int cents = get_cents();

    // Calculate the number of quarters to give the customer
    int quarters = calculate_quarters(cents);
    cents = cents - quarters * 25;

    // Calculate the number of dimes to give the customer
    int dimes = calculate_dimes(cents);
    cents = cents - dimes * 10;

    // Calculate the number of nickels to give the customer
    int nickels = calculate_nickels(cents);
    cents = cents - nickels * 5;

    // Calculate the number of pennies to give the customer
    int pennies = calculate_pennies(cents);
    cents = cents - pennies * 1;

    // Sum coins
    int coins = quarters + dimes + nickels + pennies;

    // Print total number of coins to give the customer
    printf("%i\n", coins);
}

int get_cents(void)
{
    //input floating values
    do
    {
        printf("Change owed: ");
        fgets(buffer, sizeof(buffer), stdin);
        pointer = buffer;                       // assign pointer to the base buffer (first char of buffer)
    }
    while (is_contain_char(pointer) || atof(pointer) <= 0);          // if input contains char, keep asking

    return atof(pointer);
}

int calculate_quarters(int cents)
{
    int quarters = 0;

    while (cents >= 25)
    {
        cents -= 25;
        quarters++;
    }

    return quarters;
}

int calculate_dimes(int cents)
{
    int dimes = 0;

    while (cents >= 10)
    {
        cents -= 10;
        dimes++;
    }

    return dimes;
}

int calculate_nickels(int cents)
{
    int nickels = 0;

    while (cents >= 5)
    {
        cents -= 5;
        nickels++;
    }

    return nickels;
}

int calculate_pennies(int cents)
{
    int pennies = 0;

    while (cents >= 1)
    {
        cents -= 1;
        pennies++;
    }

    return pennies;
}

bool is_contain_char(char* the_pointer)
{
    bool return_value = false;

    while (*the_pointer != '\n' && *the_pointer != '\0')    // 123 actually is "123\n\0"
    {
        if (*the_pointer < '0' || *the_pointer > '9')
            return_value = true;
        the_pointer++;
    }

    return return_value;
}
