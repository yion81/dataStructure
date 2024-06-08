#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int romanToInt(char *s)
{
    int count = 0;
    for (int i = 0; i < strlen(s); i++)
    {
        if (s[i] == 'I')
        {
            count += 1;
        }
        else if (s[i] == 'V')
        {
            count += 5;
        }
        else if (s[i] == 'X')
        {
            count += 10;
        }
        else if (s[i] == 'L')
        {
            count += 50;
        }
        else if (s[i] == 'C')
        {
            count += 100;
        }
        else if (s[i] == 'D')
        {
            count += 500;
        }
        else if (s[i] == 'M')
        {
            count += 1000;
        }
    }
    return count;
}

int main()
{
    int count = romanToInt("III");
    printf("%d", count);
}