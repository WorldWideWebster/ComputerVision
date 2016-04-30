/*--------------- arrays.c ---------------

by:   Sean Webster

PURPOSE
Array based functions for inputting images

---------------------------------------------*/

#include "arrays.h"


/*-------------------- ImageInit()-------------------------------------

PURPOSE
Initializes image float array in memory and to 0

INPUT PARAMETERS
-xsize:	size of array in x direction
-ysize: size of array in y direction
--------------------------------------------------------------------*/
float **ImageInit(int xsize, int ysize)
{
	float **data;
	int i, j;
	data = (float **)malloc(sizeof(float *) * ysize);
	for (i = 0; i < ysize; i++)
	{
		data[i] = (float *)malloc(sizeof(float) * xsize);
	}
	for (i = 0; i < ysize; i++)
	{
		for (j = 0; j < xsize; j++)
		{
			data[i][j] = 0;
		}
	}
	return data;
}




/*-------------------- OpenImage()-------------------------------------

PURPOSE
Reads a raw image file into a 2D array

INPUT PARAMETERS
-data:	2D array to be input
-xsize:	size of array in x direction
-ysize: size of array in y direction
-fn:	name of input image
--------------------------------------------------------------------*/
int OpenImage(char *fn, int xsize, int ysize, float **data)
{
	int j;
	int	k;
	FILE *fp_inp;
	unsigned char pixel;
	// Read image contents into 2D array
	if ((fp_inp = fopen(fn, "rb")) == NULL) return -1;
	for (j = 0; j < ysize; j++)
	{
		for (k = 0; k < xsize; k++)
		{
			fread(&pixel, sizeof(char), 1, fp_inp);
			data[j][k] = (float)pixel;
		}
	}

	(void)fclose(fp_inp);
	return 0;
}

/*-------------------- SaveImage()-------------------------------------

PURPOSE
Writes a 2D array to a raw image file

INPUT PARAMETERS
-data:	2D array to be input
-xsize:	size of array in x direction
-ysize: size of array in y direction
-fn:	name of input image
-out:	string to append to output image
--------------------------------------------------------------------*/
void SaveImage(float *fn, char* out, int xsize, int ysize, float **data_ptr)
{
	int j, k;
	FILE *out_file;
	char out_name[40];
	char name[15];
	unsigned char pixel;
	strcpy(name, fn);
	strcpy(out_name, name);
	strcat(out_name, out);
	out_file = fopen(out_name, "wb");
	for (j = 0; j < ysize; j++)
	{
		for (k = 0; k < xsize; k++)
		{
			pixel = (unsigned char)data_ptr[j][k];
			fwrite(&pixel, sizeof(char), 1, out_file);
		}
	}
	(void)fclose(out_file);
}

void SaveImageAsText(float *fn, char* out, int xsize, int ysize, float **data_ptr)
{
	int j, k;
	FILE *out_file;
	char out_name[20];
	char name[15];
	unsigned char pixel;
	strcpy(name, fn);
	strcpy(out_name, name);
	strcat(out_name, out);
	strcat(out_name, ".txt");
	out_file = fopen(out_name, "wb");
	for (j = 0; j < ysize - 1; j++)
	{
		for (k = 0; k < xsize - 1; k++)
		{
			pixel = (unsigned char)data_ptr[j][k];
			fwrite(&pixel, sizeof(char), 1, out_file);
		}
		fwrite("\n", sizeof(char), 1, out_file);
	}
	(void)fclose(out_file);
}

/*-------------------- SaveImage()-------------------------------------

PURPOSE
Writes to console report of accuracy

INPUT PARAMETERS
-image1:	2D image array to be compared
-image2:	2D image array to be compared
-xsize:		size of array in x direction
-ysize:		size of array in y direction
--------------------------------------------------------------------*/
void AccuracyReport(float **image1, float **image2, int xsize, int ysize) 
{
	int x, y;
	double m = xsize*ysize;
	float accuracy = 0;
	for (y = 0; y < ysize - 1; y++)
	{
		for (x = 0; x < xsize - 1; x++)
		{
			if (image1[y][x] == image2[y][x]) accuracy++;
		}
	}
	printf("Image2 contains %lf of the same pixels as Image2\n", accuracy / m);
}