#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>


typedef struct color
{
	unsigned char r;
	unsigned char g;
	unsigned char b;

} color;

void readImage(int p, char *inFile, char *outFile);
void printImage(char *fileName, int width, color **a);

//To get ppm image from jpeg file, please visit https://convertio.co/jpg-ppm/
void readImage(int p, char *inFile, char *outFile)
{
	FILE *f = fopen(inFile, "rb");

	char u[3]; // placehoder
	int width, height, max_value;
	fscanf(f, "%s%d%d%d%c", u, &width, &height, &max_value, &u[0]);

    int i;
    color **colors;
    colors = (color **)malloc(width*sizeof(color*));
    for (i = 0; i < height; i++)
        colors[i] = (color *)malloc(width*sizeof(color));
	
	for (i = 0; i < height; i++)
		fread(colors[i], sizeof(color), width, f);
	printImage(outFile, width, colors);
	fclose(f);
}

void printImage(char *fileName, int width, color **a)
{
	FILE *f = fopen(fileName, "wb");

	fprintf(f, "P6\n");
	fprintf(f, "%d %d\n", width, width);
	fprintf(f, "255\n");

	int i;
	for (i = 0; i < width; i++)
		fwrite(a[i], sizeof(color), width, f);

	fclose(f);
}

int main(int argc, char **argv)
{
	int tolerance = 0;
	char *inFile;
	char *outFile;
	if (argc > 1)
	{
		tolerance = atoi(argv[1]);
		inFile = argv[2];
		outFile = argv[3];

		readImage(tolerance, inFile, outFile);
	}
	return 0;
}