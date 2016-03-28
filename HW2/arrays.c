/*--------------- arrays.c ---------------

by:   Sean Webster

PURPOSE
Array based functions for inputting images

---------------------------------------------*/

#include "arrays.h"


/*-------------------- NormalizeArray()-------------------------------------

PURPOSE
Normalizes 2D array, then multiplies by 255

INPUT PARAMETERS
-data:	2D array to be input
-xsize:	size of array in x direction
-ysize: size of array in y direction
--------------------------------------------------------------------*/
void NormalizeArray(float **data, int xsize, int ysize)
{
	int i, j;
	float max, min, num, denom;
	max = min = data[0][0];
	for (i = 0; i < ysize; i++)
	{
		for (j = 0; j < xsize; j++)
		{
			if (data[i][j] > max)
			{
				max = data[i][j];
			}
			if (data[i][j] < min)
			{
				min = data[i][j];
			}
		}
	}
	denom = max - min;
	for (i = 0; i < ysize; i++)
	{
		for (j = 0; j < xsize; j++)
		{
			num = data[i][j] - min;
			data[i][j] = (int)(num / denom * 255);
		}
	}

}

/*-------------------- ReadIntoArray()-------------------------------------

PURPOSE
Reads a raw image file into a 2D array

INPUT PARAMETERS
-data:	2D array to be input
-xsize:	size of array in x direction
-ysize: size of array in y direction
-fn:	name of input image
--------------------------------------------------------------------*/
void ReadIntoArray(char *fn, int xsize, int ysize, unsigned char **data)
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
			data[j][k] = pixel;
		}
	}

	(void)fclose(fp_inp);
}

/*-------------------- WriteIntoArray()-------------------------------------

PURPOSE
Writes a 2D array to a raw image file

INPUT PARAMETERS
-data:	2D array to be input
-xsize:	size of array in x direction
-ysize: size of array in y direction
-fn:	name of input image
-out:	string to append to output image
--------------------------------------------------------------------*/
void WriteIntoArray(char *fn, char* out, int xsize, int ysize, float **data_ptr)
{
	int j, k;
	FILE *out_file;
	char out_name[20];
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
			pixel = data_ptr[j][k];
			fwrite(&pixel, sizeof(char), 1, out_file);
		}
	}
	(void)fclose(out_file);
}