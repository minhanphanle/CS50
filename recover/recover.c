#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

typedef uint8_t BYTE;

int main(int argc, char *argv[])
{
    //check for valid usage
    if (argc != 2)
    {
        printf("Usage: Usage: ./recover IMAGE\n");
        return 1;
    }

    //open memory card
    FILE *file = fopen(argv[1], "r");
    if (file == NULL)
    {
        printf("Could not open: %s\n", argv[1]);
        return 2;
    }

    //declare variables
    BYTE buffer[512]; //store 512 bytes in an array
    FILE *out_file = NULL; //uninitialized file pointer for recovered images
    int count_img = 0;
    char *filename = malloc(8 * sizeof(char));

    //read memory card. 512 bytes
    while (fread(buffer, sizeof(BYTE), 512, file) == 512) //
    {
        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] & 0xef) == 0xe0)
        {
            if (!(count_img == 0))
            {
                fclose(out_file);
            }
            sprintf(filename, "%03i.jpg", count_img);
            out_file = fopen(filename, "w");
            count_img++;
        }

        if (out_file != NULL)
        {
            fwrite(buffer, sizeof(BYTE), 512, out_file);
        }
    }

    fclose(file);
    fclose(out_file);
    free(filename);

    return 0;
}