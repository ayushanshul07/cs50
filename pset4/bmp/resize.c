/**
 * copy.c
 *
 * Computer Science 50
 * Problem Set 4
 *
 * Copies a BMP piece by piece, just because.
 */

#include <stdio.h>
#include <stdlib.h>

#include "bmp.h"

int main(int argc, char* argv[])
{
    // ensure proper usage
    if (argc != 4)
    {
        printf("Usage: ./resize n infile outfile\n");
        return 1;
    }


    int n = atoi(argv[1]);
    if (n < 1 || n >= 100)
    {
        printf("unable to resize ; input number between [1,100) \n");
        return 2;
    }
    // remember filenames
    char* infile = argv[2];
    char* outfile = argv[3];

    // open input file 
    FILE* inptr = fopen(infile, "r");
    if (inptr == NULL)
    {
        printf("Could not open %s.\n", infile);
        return 3;
    }

    // open output file
    FILE* outptr = fopen(outfile, "w");
    if (outptr == NULL)
    {
        fclose(inptr);
        fprintf(stderr, "Could not create %s.\n", outfile);
        return 4;
    }

    // read infile's BITMAPFILEHEADER
    BITMAPFILEHEADER bf;
    fread(&bf, sizeof(BITMAPFILEHEADER), 1, inptr);

    // read infile's BITMAPINFOHEADER
    BITMAPINFOHEADER bi;
    fread(&bi, sizeof(BITMAPINFOHEADER), 1, inptr);

    // ensure infile is (likely) a 24-bit uncompressed BMP 4.0
    if (bf.bfType != 0x4d42 || bf.bfOffBits != 54 || bi.biSize != 40 || 
            bi.biBitCount != 24 || bi.biCompression != 0)
    {
        fclose(outptr);
        fclose(inptr);
        fprintf(stderr, "Unsupported file format.\n");
        return 5;
    }
    // remember original height , width and padding
    int org_h = abs(bi.biHeight);
    int org_w = bi.biWidth; 
    int padding_org =  (4 - (bi.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;

    // new height,width and padding
    bi.biWidth *= n ; 
    bi.biHeight *= n ;
    int padding =  (4 - (bi.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;
    bi.biSizeImage = (bi.biWidth * sizeof(RGBTRIPLE) + padding) * ( abs(bi.biHeight) );
    bf.bfSize = bi.biSizeImage + 54;

    // write outfile's BITMAPFILEHEADER
    fwrite(&bf, sizeof(BITMAPFILEHEADER), 1, outptr);

    // write outfile's BITMAPINFOHEADER
    fwrite(&bi, sizeof(BITMAPINFOHEADER), 1, outptr);

    // iterate over infile's scanlines
    for (int i = 0; i < org_h ; i++)
    {
        for(int k=1; k <= n ; k++)  
        {   // iterate over pixels in scanline  
            for (int j = 0; j < org_w; j++)
            {
                // temporary storage
                RGBTRIPLE triple;

                // read RGB triple from infile
                fread(&triple, sizeof(RGBTRIPLE), 1, inptr);

                // write RGB triple to outfile
                for(int l=1;l <= n ;l++)
                    fwrite(&triple, sizeof(RGBTRIPLE), 1, outptr);

            } 
            // skip over padding, if any
            fseek(inptr, padding_org, SEEK_CUR);

            // then add it back (to demonstrate how)       
            for (int m = 0; m < padding; m++)
                fputc(0x00, outptr);

            // don't do this last time  
            if (k < n)
                fseek(inptr, -(org_w * sizeof(RGBTRIPLE) + padding_org ),SEEK_CUR);// sending cursor in infile back to start
        }        
    }

    // close infile
    fclose(inptr);

    // close outfile
    fclose(outptr);

    // that's all folks
    return 0;
}
