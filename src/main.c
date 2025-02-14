#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#define OFFSET 7

//We will work with .bmp files, and for now, only 16-bit color depth.
//Lots of error checks need to happen, but this is just for fun.

int main(int argc, char **argv)
{
    if (argc != 5)
    {
        printf("Usage: ./gaussian <img_path.bmp> <width> <height> <output_path.bmp>\n");
        exit(0);
    }
    const size_t IMG_WIDTH = atoi(argv[2]);
    const size_t IMG_HEIGHT = atoi(argv[3]);
    FILE *fp = fopen(argv[1], "rb");
    unsigned short buffer[(IMG_WIDTH * IMG_HEIGHT) + 100]; //16-bit integers.
    fread(buffer, sizeof(unsigned short),  (IMG_WIDTH * IMG_HEIGHT) + 100, fp);
    for (size_t i = (buffer[OFFSET] / 2) + OFFSET; i < IMG_WIDTH * IMG_HEIGHT; i++)
    {
        buffer[i] = 0x6d83;
    }
    unsigned short multi_buffer[IMG_WIDTH][IMG_HEIGHT];
    size_t idx = 0;
    FILE *new_file = fopen(argv[4], "wb");
    printf("Result: %zu\n", fwrite(buffer, sizeof(unsigned short), OFFSET + (IMG_WIDTH * IMG_HEIGHT), new_file));
    fclose(fp);
    fclose(new_file);
    
    return 0;
}
