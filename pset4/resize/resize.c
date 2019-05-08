// Copies a BMP file

#include <stdio.h>
#include <stdlib.h>

#include "bmp.h"

int main(int argc, char *argv[])
{
    // ensure proper usage
    if (argc != 4)
    {
        fprintf(stderr, "Usage: resize n infile outfile\n");
        return 1;
    }
    // check 0<n<=100
    int n;
    n = atoi(argv[1]);
    if (n <= 0 || n > 100)
    {
        fprintf(stderr, "n must be a positive int less than or equal to 100\n");
        return 5;
    }
    // remember filenames
    char *infile = argv[2];
    char *outfile = argv[3];

    // open input file
    FILE *inptr = fopen(infile, "r");
    if (inptr == NULL)
    {
        fprintf(stderr, "Could not open %s.\n", infile);
        return 2;
    }

    // open output file
    FILE *outptr = fopen(outfile, "w");
    if (outptr == NULL)
    {
        fclose(inptr);
        fprintf(stderr, "Could not create %s.\n", outfile);
        return 3;
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
        return 4;
    }
    // determine padding for scanlines in input image
    int padding1 = (4 - (bi.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;
    BITMAPFILEHEADER bf2;
    bf2 = bf;
    BITMAPINFOHEADER bi2;
    bi2 = bi;

    // updating header info
    bi2.biWidth = bi.biWidth*n;
    bi2.biHeight = bi.biHeight*n;
    // determine padding for scanlines in output image
    int padding2 = (4 - (bi2.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;
    bi2.biSizeImage = ((sizeof(RGBTRIPLE)*bi2.biWidth)+padding2)*abs(bi2.biHeight);
    bf2.bfSize = bi2.biSizeImage + sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER);

    // write outfile's BITMAPFILEHEADER
    fwrite(&bf2, sizeof(BITMAPFILEHEADER), 1, outptr);

    // write outfile's BITMAPINFOHEADER
    fwrite(&bi2, sizeof(BITMAPINFOHEADER), 1, outptr);

    int count = 1;
    // iterate over infile's scanlines
    for (int i = 0, bi2Height = abs(bi2.biHeight); i < bi2Height; i++)
    {
        // iterate over pixels in scanline
        for (int j = 0; j < bi.biWidth; j++)
        {
            // temporary storage
            RGBTRIPLE triple;
            // read RGB triple from infile
            fread(&triple, sizeof(RGBTRIPLE), 1, inptr);
            // write RGB triple to outfile
            for(int m = 0; m < n; m++)
            {
                fwrite(&triple, sizeof(RGBTRIPLE), 1, outptr);
            }
        }
        // add padding in output file
        for (int k = 0; k < padding2; k++)
        {
           fputc(0x00, outptr);
        }

        if (count < n)
        {
            fseek(inptr, -bi.biWidth*3, SEEK_CUR);
            count++;
        }
        else
        {
        // skip over padding, if any in input file
        fseek(inptr, padding1, SEEK_CUR);
        count = 1;
        }
    }
    // close infile
    fclose(inptr);

    // close outfile
    fclose(outptr);

    // success
    return 0;
}
