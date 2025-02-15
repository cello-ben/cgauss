#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#define OFFSET 7
#define EACH_N 200

//We will work with .bmp files, and for now, only 16-bit color depth.
//Lots of error checks need to happen for production code; this is just for fun.


int main(int argc, char **argv)
{
    if (argc != 5)
    {
        printf("Usage: ./cgauss <img_path.bmp> <width> <height> <output_path.bmp>\n");
        exit(0);
    }

    const size_t IMG_WIDTH = atoi(argv[2]);
    const size_t IMG_HEIGHT = atoi(argv[3]);

    const size_t USHORT_SZ = sizeof(unsigned short);
    
    unsigned short **pixels = malloc(USHORT_SZ * IMG_WIDTH * IMG_HEIGHT);
    for (size_t i = 0; i < IMG_WIDTH; i++)
    {
        pixels[i] = malloc(USHORT_SZ * IMG_HEIGHT);
        for (size_t j = 0; j < IMG_HEIGHT; j++)
        {
            pixels[i][j] = 0;
        }
    }

    FILE *fp = fopen(argv[1], "rb");

    if (fp == NULL)
    {
        printf("Failed to open path for input file.\n");
        return -1;
    }

    unsigned short buffer[(IMG_WIDTH * IMG_HEIGHT) + 100]; //16-bit integers, at least on my machine.
    fread(buffer, USHORT_SZ, (IMG_WIDTH * IMG_HEIGHT) + 100, fp);
    fclose(fp);

    // for (size_t i = (buffer[OFFSET] / 2) + OFFSET; i < IMG_WIDTH * IMG_HEIGHT; i++)
    // {
    //     buffer[i] = 0x6d83; //Set each pixel to lime green-ish color for testing.
    // }
    unsigned short multi_buffer[IMG_WIDTH][IMG_HEIGHT];
    size_t idx = (buffer[OFFSET] / 2) + OFFSET;
    for (size_t i = 0; i < IMG_WIDTH; i++)
    {
        for (size_t j = 0; j < IMG_HEIGHT; j++)
        {
            multi_buffer[i][j] = buffer[idx++];
        }
    }

    //Now we do the manipulation of the pixels. 
    //We'll start with trying out a box blur to make things a bit simpler.
    //Plain old box blur from pseudocode I found on Wikipedia is super noisy. 
    //Being selective about how many pixels we want to alter makes it better.
    //New idea: try just doing multiple passes of box blur.

        idx = (buffer[OFFSET] / 2) + OFFSET;
        for (size_t i = 0; i < IMG_WIDTH; i++)
        {
            for (size_t j = 0; j < IMG_HEIGHT; j++)
            {
                multi_buffer[i][j] = buffer[idx++];
            }
        }

        idx = (buffer[OFFSET] / 2) + OFFSET;
        for (size_t i = 0; i < IMG_WIDTH; i++)
        {
            for (size_t j = 0; j < IMG_HEIGHT; j++)
            {
                buffer[idx++] = multi_buffer[i][j];
            }
        }

        idx = (buffer[OFFSET] / 2) + OFFSET;
        for (size_t i = 2; i < IMG_WIDTH - 2; i++)
        {
            for (size_t j = 2; j < IMG_HEIGHT - 2; j++)
            {
                int sum = multi_buffer[i][j] * 25;
                if (1 == 1)
                {
                    sum = multi_buffer[i - 2][j - 2] +
                    multi_buffer[i - 2][j-1] +
                    multi_buffer[i - 2][j] +
                    multi_buffer[i - 2][j + 1] +
                    multi_buffer[i - 2][j + 2] +
                    multi_buffer[i - 1][j - 2] +
                    multi_buffer[i - 1][j - 1] +
                    multi_buffer[i - 1][j] +
                    multi_buffer[i - 1][j + 1] +
                    multi_buffer[i - 1][j + 2] +
                    multi_buffer[i][j - 2] +
                    multi_buffer[i][j - 1] +
                    multi_buffer[i][j] +
                    multi_buffer[i][j + 1] +
                    multi_buffer[i][j + 2] +
                    multi_buffer[i + 1][j - 2] +
                    multi_buffer[i + 1][j - 1] +
                    multi_buffer[i + 1][j] +
                    multi_buffer[i + 1][j + 1] +
                    multi_buffer[i + 1][j + 2] +
                    multi_buffer[i + 2][j - 2] +
                    multi_buffer[i + 2][j - 1] +
                    multi_buffer[i + 2][j] +
                    multi_buffer[i + 2][j + 1] +
                    multi_buffer[i + 2][j + 2];
                }
            buffer[idx++] = sum / 5;
            }
        }
    

    FILE *new_file = fopen(argv[4], "wb");
    if (new_file == NULL)
    {
        printf("Failed to open path for new file.\n");
        return -1;
    }
    if(fwrite(buffer, USHORT_SZ, (IMG_WIDTH * IMG_HEIGHT) + 100, new_file) == 0)
    {
        printf("Nothing written.\n");
        return -1;
    }
    for (size_t i = 0; i < IMG_WIDTH; i++)
    {
        free(pixels[i]);
    }
    free(pixels);
    fclose(new_file);
    
    return 0;
}
