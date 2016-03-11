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
	unsigned char **data = Init2DChar(data, xsize, ysize);
	float **spectrum = Init2DFloat(spectrum, xsize*2, ysize*2);

	ReadIntoArray("mri", 256, 256, data);

	for (i = 0; i < ysize; i++)
	{
		for (j = 0; j < xsize; j++)
		{
			spectrum[i][j] = (float)data[i][j];
		}
	}
	
	float **real = Init2DFloat(real, xsize, ysize);
	float **imag = Init2DFloat(imag, xsize, ysize);

	four2(spectrum, 256, 256, 1, real, imag);

	float** filter = Init2DFloat(filter, xsize * 2, ysize * 2);

	for (i = 0; i < ysize; i++)
	{
		for (j = 0; j < xsize; j++)
		{
			filter[i][j] = (float)spectrum[i][j];
		}
	}


	Butterworth(filter, real, imag, xsize, ysize, 1);
	NormalizeArray(spectrum, 256, 256);

	WriteIntoArray("mri", "_spectrum", 256, 256, spectrum);

	four2(filter, 256, 256, -1, real, imag);
	WriteIntoArray("mri", "_butterworth", 256, 256, filter);


	free(data);
	free(spectrum);
	free(real);


	return 0;
}

