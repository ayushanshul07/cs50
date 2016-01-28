#include <stdio.h>  
#include <cs50.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

int main(int argc, string argv[])
{
    if (argc != 2)
    {
        printf("usage : ./caesar key\n");
        return 1;
    }   

    int key = atoi(argv[1]);
    string plaintext = GetString();

    for(int i = 0 ; i < strlen(plaintext) ;++i)
    {
        if (isalpha(plaintext[i]))
        {
            if (isupper(plaintext[i]))
            {
                int index = plaintext[i] - 65 ;
                index = (index + key ) % 26 ;
                index = index + 65;
                printf("%c",index);
            }
            if (islower(plaintext[i]))
            {
                int index = plaintext[i] - 97 ;
                index = (index + key ) % 26 ;
                index = index + 97;
                printf("%c",index); 
            }
        }
        else
        {
            printf("%c",plaintext[i]);
        }
    }

    printf("\n");
    return 0;
}
