#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "QuadTree.h"

color **colors;

int readImage(char *_inFile, color ***_pic_p, int *_width, int *_height);
int printImage(char *fileName, color **pic, int width, int height);

int main(int argc, char *argv[])
{
    int tolerance = 0;
    char *inFile;
    char *outFile;
    if (argc < 4)
    {
        printf("Usage: %s <tolerance> <input file> <output file>\n", argv[0]);
        return 1;
    }

    tolerance = atoi(argv[1]);
    inFile = argv[2];
    outFile = argv[3];

    int width, height;
    int res = readImage(inFile, &colors, &width, &height);
    if (res == 0){
        printf("readImage failed\n");
        return 1;
    }
    printf("r: %d, g: %d, b: %d\n", colors[0][0].r, colors[0][0].g, colors[0][0].b);
    quad_process(colors, width, height, tolerance);

    printImage(outFile, colors, width, height);

    // free memory
    for (int i = 0; i < width; i++)
        free(colors[i]);
    free(colors);
    return 0;
}
/*
    readImage: read image from file
    return value: 1 if success, 0 if fail
*/
int readImage(char *_inFile, color ***_pic_p, int *_width, int *_height)
{
    FILE *f = fopen(_inFile, "rb");
    if (f == NULL)
    {
        printf("Cannot open file %s\n", _inFile);
        return 0;
    }

    char u[3];
    int width, height, max_value;
    fscanf(f, "%s%d%d%d%c", u, &width, &height, &max_value, &u[0]);
    *_width = width;
    *_height = height;
    int i;

    *_pic_p = (color **)malloc(height * sizeof(color *));

    for (i = 0; i < height; i++)
        (*_pic_p)[i] = (color *)malloc(width * sizeof(color));

    for (i = 0; i < height; i++)
        fread((*_pic_p)[i], sizeof(color), width, f);
    fclose(f);

    return 1;
}

/*
    printImage: print image to file
    return value: 1 if success, 0 if fail
*/
int printImage(char *fileName, color **pic, int width, int height)
{
    FILE *f = fopen(fileName, "wb");
    if (f == NULL)
    {
        printf("Cannot open file %s\n", fileName);
        return 0;
    }

    fprintf(f, "P6\n");
    fprintf(f, "%d %d\n", width, height);
    fprintf(f, "255\n");

    int i;
    for (i = 0; i < height; i++)
        fwrite(pic[i], sizeof(color), width, f);

    fclose(f);
    return 1;
}