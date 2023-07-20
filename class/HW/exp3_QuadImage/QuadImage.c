#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>
#include "QuadTree.h"
color** colors;

int readImage(char* _inFile, color*** _pic_p, int* _width, int* _height);
int printImage(char* fileName, color** pic, int width, int height);
void gauss_blur(color** _pic, int _width, int _height);

int main(int argc, char* argv[])
{
    int tolerance = 0;
    char* inFile;
    char* outFile;
    if (argc < 4)
    {
        printf("Usage: %s <tolerance> <input file> <output file>\n", argv[0]);
        return 1;
    }

    tolerance = atoi(argv[1]);
    inFile = argv[2];
    outFile = argv[3];

    int width, height;
    // allocate memory for image
    int res = readImage(inFile, &colors, &width, &height);
    if (res == 0) {
        printf("readImage failed\n");
        return 1;
    }
    // image_integral(colors, width, height);
    double start = clock();
    quad_process(colors, width, height, tolerance);
    double end = clock();
    printf("time: %lfs\n", (end - start) / CLOCKS_PER_SEC);
    // gauss_blur(colors, width, height);
    printImage(outFile, colors, width, height);

    // free memory
    for (int i = 0; i < height; i++)
        free(colors[i]);
    free(colors);
    return 0;
}
/*
    readImage: read image from file
    return value: 1 if success, 0 if fail
*/
int readImage(char* _inFile, color*** _pic_p, int* _width, int* _height)
{
    FILE* f = fopen(_inFile, "rb");
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

    *_pic_p = (color**)malloc(height * sizeof(color*));

    for (i = 0; i < height; i++)
        (*_pic_p)[i] = (color*)malloc(width * sizeof(color));


    for (i = 0; i < height; i++)
        fread((*_pic_p)[i], sizeof(color), width, f);
    fclose(f);

    return 1;
}

/*
    printImage: print image to file
    return value: 1 if success, 0 if fail
*/
int printImage(char* fileName, color** pic, int width, int height)
{
    FILE* f = fopen(fileName, "wb");
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

/*
    GaussianBlur: blur the image with Gaussian kernel
*/
void gauss_blur(color** _pic, int _width, int _height) {
    double kernel[5][5] = {
        {1.0 / 273, 4.0 / 273, 7.0 / 273, 4.0 / 273, 1.0 / 273},
        {4.0 / 273, 16.0 / 273, 26.0 / 273, 16.0 / 273, 4.0 / 273},
        {7.0 / 273, 26.0 / 273, 41.0 / 273, 26.0 / 273, 7.0 / 273},
        {4.0 / 273, 16.0 / 273, 26.0 / 273, 16.0 / 273, 4.0 / 273},
        {1.0 / 273, 4.0 / 273, 7.0 / 273, 4.0 / 273, 1.0 / 273}
    };
    for (int i = 2; i < _height - 2; i++)
    {
        for (int j = 2; j < _width - 2; j++)
        {
            double r = 0, g = 0, b = 0;
            for (int k = -2; k <= 2; k++)
            {
                for (int l = -2; l <= 2; l++)
                {
                    r += _pic[i + k][j + l].r * kernel[k + 2][l + 2];
                    g += _pic[i + k][j + l].g * kernel[k + 2][l + 2];
                    b += _pic[i + k][j + l].b * kernel[k + 2][l + 2];
                }
            }
            _pic[i][j].r = (unsigned char)r;
            _pic[i][j].g = (unsigned char)g;
            _pic[i][j].b = (unsigned char)b;
        }
    }


}

