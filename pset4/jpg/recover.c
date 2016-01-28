#include <stdio.h>

#define BUFFER 512

int main(int argc, char* argv[])
{
    FILE* fp = fopen("card.raw","r");
    if (fp == NULL)
    {
        printf("cannot open file 'card.raw'\n ");
        return 1;
    }

    unsigned char block[BUFFER];

    do
    {
        fread( &block, BUFFER , 1 , fp );
        if ( block[0] == 0xff && block[1] == 0xd8 && block[2] == 0xff && block[3] == 0xe0)
            break;
        else if ( block[0] == 0xff && block[1] == 0xd8 && block[2] == 0xff && block[3] == 0xe1)
            break;
    }    
    while  ( 1 );

    char title[10];
    int k = 0;
    do
    {
        int flag = 0;
        sprintf(title,"%.3d.jpg",k);
        FILE* image = fopen(title,"a");
        if (image == NULL)
        {
            printf("Could not create new image.\n ");
            return 2;
        }
        fwrite(&block, BUFFER , 1 , image);
        if ( fread( &block, BUFFER , 1 , fp ) == 0 )
        {
            fclose(image);
            break;
        }	

        while  ( 1 )
        {	
            if (block[0] == 0xff && block[1] == 0xd8 && block[2] == 0xff && block[3] == 0xe0)
                break;
            else if (block[0] == 0xff && block[1] == 0xd8 && block[2] == 0xff && block[3] == 0xe1)
                break;

            fwrite(&block, BUFFER , 1 ,image);

            if (fread( &block, BUFFER , 1 , fp ) == 0)
            {
                flag = 1;
                break;
            }

        }

        if (flag == 1)
            break;
        else
            k++;

        fclose(image);

    }
    while( 1 );

    fclose(fp);
    return 0;

}



