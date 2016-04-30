/*--------------- Spacial.c ---------------
PURPOSE: Holds functions for spacial image manipulation

by:		Sean Webster
		Computer Vision
		Due 4/4/2016
---------------------------------------------*/
#include "Spacial.h"


/*-------------------- PadImage()-------------------------------------

PURPOSE
Pads image, adding 0's for spacial filtering

INPUT PARAMETERS
-inData:	old 2D array to be input
-outData:	new 2D array to be input
-xsize:		size of array in x direction
-ysize:		size of array in y direction
--------------------------------------------------------------------*/
void PadImage(float **inData, float **outData, int xsize, int ysize, int pSize)
{
	int i, j;
	for (i = 0; i < ysize; i++)
	{
		for (j = 0; j < xsize; j++)
		{
				outData[i + pSize][j + pSize] = inData[i][j];
		}
	}
}


/*-------------------- Sobel()-------------------------------------

PURPOSE
Masks image with sobel operator

INPUT PARAMETERS
-inData:	old 2D array to be input
-outData:	new 2D array to be input
-xsize:		size of array in x direction
-ysize:		size of array in y direction
--------------------------------------------------------------------*/
void Sobel(float **inData, float **outData, int xsize, int ysize)
{
	float **temp1 = ImageInit(xsize, ysize);
	float **temp2 = ImageInit(xsize, ysize);
	
	int vertKernel[3][3] =	{	{ -1,  0,  1 },
								{ -2,  0,  2 },
								{ -1,  0,  1 } };
	int horzKernel[3][3] = {	{ 1,  2,  1 },
								{ 0,  0,  0 },
								{ -1, -2, -1 } };


	int x, y, i, j;
	double pixel_value;
	double max = -DBL_MAX;

	//Vertical Sobel Mask
	for (y = 1; y < ysize - 1; y++)
	{
		for (x = 1; x < xsize - 1; x++)
		{
			pixel_value = 0.0;
			for (j = -1; j <= 1; j++) {
				for (i = -1; i <= 1; i++) {
					pixel_value += vertKernel[j + 1][i + 1] * inData[y + j][x + i];
				}
			}
			
			temp1[y - 1][x - 1] = pixel_value;
		}
	}

	// Horizontal Sobel Mask
	for (y = 1; y < ysize - 1; y++)
	{
		for (x = 1; x < xsize - 1; x++)
		{
			pixel_value = 0.0;
			for (j = -1; j <= 1; j++) {
				for (i = -1; i <= 1; i++) {
					pixel_value += horzKernel[j + 1][i + 1] * inData[y + j][x + i];
				}
			}
			temp2[y - 1][x - 1] = pixel_value;
		}
	}

	// Take magnitude
	for (y = 0; y < ysize - 3; y++)
	{
		for (x = 0; x < xsize - 3; x++)
		{
			outData[y][x] = sqrt(pow(temp1[y][x], 2) + pow(temp2[y][x], 2));
			// Get max for normalizing
			if (outData[y][x] > max) max = outData[y][x];
		}
	}
	// Normalize
	for (y = 0; y < ysize - 3; y++)
	{
		for (x = 0; x < xsize - 3; x++)
		{
			outData[y][x] = 255 * outData[y][x] / max;
		}
	}

	free(temp1);
	free(temp2);
}

/*-------------------- BinThresh()-------------------------------------

PURPOSE
Takes binary threshold of image

INPUT PARAMETERS
-inData:	old 2D array to be input
-outData:	new 2D array to be input
-xsize:		size of array in x direction
-ysize:		size of array in y direction
-thresh:	threshold value
--------------------------------------------------------------------*/
void BinThresh(float **inData, float **outData, int xsize, int ysize, int thresh)
{
	int x, y;
	for (y = 1; y < ysize - 1; y++)
	{
		for (x = 1; x < xsize - 1; x++)
		{
			if (inData[y][x] > thresh)
				outData[y][x] = 255;
			else
				outData[y][x] = 0;
		}
	}
}

/*-------------------- AddUniNoise()-------------------------------------

PURPOSE
Adds uniform noise to image

INPUT PARAMETERS
-inData:	old 2D array to be input
-outData:	new 2D array to be input
-xsize:		size of array in x direction
-ysize:		size of array in y direction
-intens:	intensity of noise
--------------------------------------------------------------------*/
void AddUniNoise(float** inData, float **outData, int xsize, int ysize, int intens) 
{
	int r;
	int i = intens;
	float noise, k;
	int x, y;
	for (y = 0; y < ysize; y++) 
	{
		for (x = 0; x < xsize; x++) 
		{
			r = rand();
			k = (2 * r - RAND_MAX);
			k /= RAND_MAX;
			noise = k*i;
			outData[y][x] = inData[y][x] + noise;
		}
	}
}

/*-------------------- GaussianSmooth()-------------------------------------

PURPOSE
Applies gaussian smoothing operator to image

INPUT PARAMETERS
-inData:	old 2D array to be input
-outData:	new 2D array to be input
-xsize:		size of array in x direction
-ysize:		size of array in y direction
--------------------------------------------------------------------*/
void GaussianSmooth(float **inData, float **outData, int xsize, int ysize)
{
	float gaussKernel[3][3] = {	{ 1.0/16, 1.0/8, 1.0/16 },
								{ 1.0/8 , 1.0/4, 1.0/8  },
								{ 1.0/16, 1.0/8, 1.0/16 } };

	int x, y, i, j;
	double pixel_value;
	double max, min;

	min = DBL_MAX;
	max = -DBL_MAX;
	for (y = 1; y < ysize - 1; y++)
	{
		for (x = 1; x < xsize - 1; x++)
		{
			pixel_value = 0.0;
			for (j = -1; j <= 1; j++) {
				for (i = -1; i <= 1; i++) {
					pixel_value += gaussKernel[j + 1][i + 1] * inData[y + j][x + i];
				}
			}
			
			outData[y - 1][x - 1] += pixel_value;
		}
	}
}