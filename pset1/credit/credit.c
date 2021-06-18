#include <cs50.h>
#include <stdio.h>

bool checkLuhnAlgo(long cardNum);

int main(void)
{
    long cardNum = get_long("Number: ");
    
    luhnAlgo(cardNum);
}

//the checksum
bool checkLuhnAlgo(long cardNum)
{

}