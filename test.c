#include <stdio.h>
#include <stdlib.h>
#include <cs50.h>
#include <string.h>
#include <ctype.h>
#include <math.h>


int main(void)
{
    string p = "hello";
    string c = p;
    for (int i = 0, n = strlen(p); i < n; i++)
    {
        c[i] = p[i] + 1;
    }

    printf("%s\n",p);
    printf("%s\n",c);

}