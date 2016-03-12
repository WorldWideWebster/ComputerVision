/*--------------- four2.c ---------------

by:   Sean Webster

PURPOSE
Takes fourier transform of images, and applies filters in frequency domain

---------------------------------------------*/

#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "arrays.h"
#include "filtering.h"

int main()
{
	int i, j;
	int ysize = 256;
	int xsize = 256;

	// Assign memory
	unsigned char **inputImage = (unsigned char **)malloc(sizeof(unsigned char *) * ysize);
	for (i = 0; i < ysize; i++)
	{
		inputImage[i] = (unsigned char *)malloc(sizeof(unsigned char) * xsize);
	}
	float **spectrum = (float **)malloc(sizeof(float *) * ysize*2);
	for (i = 0; i < ysize*2; i++)
	{
		spectrum[i] = (float *)malloc(sizeof(float) * xsize*2);
	}
	float **real = (float **)malloc(sizeof(float *) * ysize);
	for (i = 0; i < ysize; i++)
	{
		real[i] = (float *)malloc(sizeof(float) * xsize);
	}
	float **imag = (float **)malloc(sizeof(float *) * ysize);
	for (i = 0; i < ysize; i++)
	{
		imag[i] = (float *)malloc(sizeof(float) * xsize);
	}
	float** filter = (float **)malloc(sizeof(float *) * ysize*2);
	for (i = 0; i < ysize * 2; i++)
	{
		filter[i] = (float *)malloc(sizeof(float) * xsize * 2);
	}
	// Assign memory

	ReadIntoArray("mri", 256, 256, inputImage);

	for (i = 0; i < ysize; i++)
	{
		for (j = 0; j < xsize; j++)
		{
			spectrum[i][j] = (float)inputImage[i][j];
		}
	}
	
	four2(spectrum, 256, 256, 1, real, imag);

	for (i = 0; i < ysize; i++)
	{
		for (j = 0; j < xsize; j++)
		{
			filter[i][j] = spectrum[i][j];
		}
	}

	//Butterworth(filter, real, imag, xsize, ysize, 1);

	WriteIntoArray("mri", "_spectrum", 256, 256, spectrum);
	four2(spectrum, 256, 256, -1, real, imag);
	WriteIntoArray("mri", "_ispectrum", 256, 256, spectrum);
	// Take inverse of filtered image
	//four2(filter, 256, 256, -1, real, imag);
	//WriteIntoArray("mri", "_butterworth", 256, 256, filter);


	free(inputImage);
	free(spectrum);
	free(real);
	free(imag);



	return 0;
}

