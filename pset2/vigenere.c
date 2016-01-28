#include <stdio.h>  
#include <cs50.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

int main(int argc, string argv[])
{
    if (argc != 2)
    {   
        printf("usage : ./caesar keyword\n");
        return 1;
    } 
    else
    {
        for(int i = 0 ; i < strlen(argv[1]) ;++i)
        {
            if (!(isalpha(argv[1][i])))
            {
                printf("usage : ./caesar keyword\n");
                return 1;
            }
        }
    }  

    string keyword = argv[1];
    int length = strlen(keyword);

    for(int i = 0 ; i < length ;++i)
        keyword[i] = toupper(keyword[i]);


    string plaintext = GetString();

    for(int i = 0, j=0 ; i < strlen(plaintext) ;++i)
    {
        if (isalpha(plaintext[i]))
        { 
            if (isupper(plaintext[i]))
            {
                if ( j >= length)
                    j = j % length;

                int index = plaintext[i] - 65 ;
                index = (index + (keyword[j] - 65)) % 26 ;
                index = index + 65;
                printf("%c",index);
                j++;
            }
            if (islower(plaintext[i]))
            {
                if ( j >= length)
                    j = j % length;

                int index = plaintext[i] - 97 ;
                index = (index + (keyword[j] - 65) ) % 26 ;
                index = index + 97;
                printf("%c",index);
                j++; 
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
