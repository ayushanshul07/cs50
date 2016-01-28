#include <stdio.h>
#include <cs50.h>

int main(void)
{
    int height;
    do
    {
        printf("height :");
        height = GetInt();
    }
    while(height < 0 || height > 23);


    for(int i = 1 ; i <= (height) ; i++)
    {
        for(int j=1 ; j <= ((height + 1) - (i + 1 )) ; j++)
        {
            printf(" ");
        }
        for(int k = 1; k <= (i + 1) ;k++)
        {
            printf("#");
        }
        printf("\n");
    }

}
