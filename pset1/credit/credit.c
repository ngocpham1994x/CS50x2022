#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define MAX_LENGTH 100

char buffer[MAX_LENGTH];
char* pointer;
int check_sum = 0;
char* card_type;
char first_two_digit[3];

//prototype
bool is_contain_char(char* the_buffer);
bool check_luhn(void);
void check_card_type(void);

int main (void)
{
    do
    {
        printf("Number: ");
        fgets(buffer, sizeof(buffer), stdin);   // get user input
        pointer = buffer;                       // assign pointer to the base buffer (first char of buffer)
    }
    while (is_contain_char(pointer));          // if input contains char, keep asking

    // 4003600000000014
    if (check_luhn())
        check_card_type();
    else
        card_type = "INVALID\n";

    printf("%s", card_type);

    // printf ("Program completed successfully.\n\n");
    return EXIT_SUCCESS;
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


bool check_luhn(void)
{
    bool valid = false;
    int length = strlen(buffer) - 1;
    char local_buffer[length];
    strcpy(local_buffer, buffer);

    char product_str[MAX_LENGTH];

    // verify other digits
    for (int i = length - 2; i >= 0; i -= 2)
    {
        char other_digit = local_buffer[i];
        int product = atoi(&other_digit) * 2;
        sprintf(product_str, "%d", product);

        for (int j = 0; j < strlen(product_str); j++)
        {
            char product_str_digit = product_str[j];
            int product_digit = atoi(&product_str_digit);
            check_sum += product_digit;
        }
    }

    // the digits that weren’t multiplied by 2, starting from the end
    for (int i = length - 1; i >= 0; i -= 2)
    {
        char digit_str = local_buffer[i];
        int digit = atoi(&digit_str);

        check_sum += digit;
    }

    // If the total’s last digit is 0 (or, put more formally, if the total modulo 10 is congruent to 0),
    // the number is valid!
    if (check_sum % 10 == 0)
        valid = true;

    // printf("check_sum: ==%d==\n\n", check_sum);
    return valid;
}

void check_card_type(void)
{
    for (int i = 0; i < 2; i++)
        first_two_digit[i] = buffer[i];

    int start_number = atoi(&first_two_digit[0]);
    int length = strlen(buffer) - 1; // remove \n

    if ( length == 15 && (start_number == 34 || start_number == 37) )
        card_type = "AMEX\n";

    else if ( length == 16 && (start_number >= 51 && start_number <= 55) )
        card_type = "MASTERCARD\n";

    else if ( (length == 13 || length == 16) && first_two_digit[0] == '4' )
        card_type = "VISA\n";

    else
        card_type = "INVALID\n";
}
