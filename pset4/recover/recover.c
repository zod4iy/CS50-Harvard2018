#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

typedef uint8_t  BYTE;
//int_least8_t  uint8_t int_fast8_t
int main(int argc, char* argv[])
{
    if (argc != 2)
    {
        fprintf(stderr, "Usage: ./recover infile\n");
        return 1;
    }

    //remember filename
    char * infile = argv[1];

    //open infile
    FILE* inptr = fopen(infile, "r");
    if (inptr == NULL)
    {
        fprintf(stderr, "Can not open %s \n", infile);
        return 2;
    }

    // find a size of input file
    long long file_size;
    fseek(inptr, 0, SEEK_END);
    file_size = ftell(inptr);
    fseek(inptr, 0, SEEK_SET);

    // find a number of blocks = 512b
    int number = file_size/512;

    // find a number of lost photos
    BYTE *buffer = malloc(512);
    int number_photo = 0;
    for (int a = 0; a < number; a++)
    {
        fread (buffer, sizeof(BYTE), 512, inptr);
        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && ((buffer[3]) & 0xf0) == 0xe0)
        {
            number_photo++;
        }
    }
    fseek(inptr, 0, SEEK_SET);
    int first_jpg;
    do
    {
        fread (buffer, sizeof(BYTE), 512, inptr);
    }
    while (buffer[0] != 0xff && buffer[1] != 0xd8 && buffer[2] != 0xff && (buffer[3] & 0xf0) != 0xe0);

    first_jpg = ftell(inptr)/512;
    for (int j = 0; j < number_photo; j++)
    {
         // create ###.jpg file
          char *filename = malloc(10);
          sprintf(filename, "%03i.jpg", j);
          FILE* img = fopen(filename, "w");
          fwrite(buffer, 1, 512, img);
          fread (buffer, 1, 512, inptr);
          for(int i = first_jpg+1; i < number; i++)
          {
              if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] & 0xf0) == 0xe0)
              {
                  break;
              }
              else if (feof(inptr) == 0)
              {
                  fwrite(buffer, 1, 512, img);
                  fread (buffer, 1, 512, inptr);
              }
          }
          fclose(img);
          free(filename);
    }
    fclose (inptr);
    free(buffer);
    return 0;
}
