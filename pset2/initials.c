#include <stdio.h>
#include <cs50.h>
#include <string.h>

void capitalise(char a)
{
    if (a >= 'a' && a <= 'z')
        a = a - ('a' - 'A');

    printf("%c",a);
}

int main(void)
{
    string text = GetString();
    int i;
    capitalise(text[0]);
    for(i = 1 ; i < strlen(text) ; i++) 
    {
        if (text[i] == ' ')
            capitalise(text[i + 1]);
    }

    printf("\n");
}

