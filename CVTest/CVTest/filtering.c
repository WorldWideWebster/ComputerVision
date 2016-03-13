/*--------------- filtering.c ---------------

by:   Sean Webster

PURPOSE
Filtering based functions for images

---------------------------------------------*/

#include "filtering.h"


/*-------------------- four1()-------------------------------------

PURPOSE
Fourier transform of 1D array.

INPUT PARAMETERS
-data:	array to be input
-nn:	size of array
-isign: inverse or forwards
--------------------------------------------------------------------*/

void four1(float *data, int nn, int isign)
{
	int n, mmax, m, j, istep, i;
	double wtemp, wr, wpr, wpi, wi, theta;
	float tempr, tempi;							// Temp real, temp imaginary 
	n = nn << 1;									// Multiply nn by 2, for complex
	j = 1;
	// Bit reversal
	for (i = 1; i<n; i += 2)
	{
		if (j > i)
		{
			SWAP(data[j], data[i]);
			SWAP(data[j + 1], data[i + 1]);
		}
		m = n >> 1;
		while (m >= 2 && j > m)
		{
			j -= m;
			m >>= 1;
		}
		j += m;
	}
	// Compute FFT
	mmax = 2;
	while (n > mmax)
	{
		istep = 2 * mmax;
		theta = 6.28318530717959 / (isign*mmax);		//2 pi radians / isign*mmax
		wtemp = sin(0.5*theta);
		wpr = -2.0*wtemp*wtemp;
		wpi = sin(theta);
		wr = 1.0;										// Real component
		wi = 0.0;										// Imaginary Component
		for (m = 1; m<mmax; m += 2)
		{
			for (i = m; i <= n; i += istep)
			{
				j = i + mmax;
				tempr = wr*data[j] - wi* data[j + 1];
				tempi = wr*data[j + 1] + wi*data[j];
				data[j] = data[i] - tempr;
				data[j + 1] = data[i + 1] - tempi;
				data[i] += tempr;
				data[i + 1] += tempi;
			}
			wr = (wtemp = wr)*wpr - wi*wpi + wr;
			wi = wi*wpr + wtemp*wpi + wi;
		}
		mmax = istep;
	}

}


/*-------------------- GetSpectrum()-------------------------------------

PURPOSE
Take absolute value of 2D array

INPUT PARAMETERS
-data:	2D array to be input
-xsize:	size of array in x direction
-ysize: size of array in y direction
-real:	2D array of real numbers
-imag:	2D array of imaginary numbers
--------------------------------------------------------------------*/
void GetSpectrum(float **data, float **real, float **imag, int xsize, int ysize)
{
	int ycount, xcount;
	float magnitude;
	for (ycount = 0; ycount < ysize; ycount++)
	{
		for (xcount = 0; xcount < xsize; xcount++)
		{
			magnitude = sqrt(powf(real[ycount][xcount], 2) + powf(imag[ycount][xcount], 2));
			data[ycount][xcount] = magnitude;
		}
	}
}

/*-------------------- iFour2Prep()-------------------------------------

PURPOSE
Preps data to take inverse 2D fourier transform

INPUT PARAMETERS
-data:	2D array to be input
-xsize:	size of array in x direction
-ysize: size of array in y direction
-real:	2D array of real numbers
-imag:	2D array of imaginary numbers
--------------------------------------------------------------------*/
void iFour2Prep(float **data, float **real, float **imag, int xsize, int ysize)
{
	int xcount, ycount;
	for (ycount = 0; ycount < ysize; ycount++)
	{
		for (xcount = 0; xcount < xsize*2; xcount += 2)
		{
			data[ycount][xcount] = real[ycount][xcount / 2];
			data[ycount][xcount + 1] = imag[ycount][xcount / 2];
		}
	}
}



/*-------------------- SpacialTransform()-------------------------------------

PURPOSE
Take spacial transform of 2D array

Inputs:
-data:	2D array to be input
-xsize:	number of pixels in x direction
-ysize: number of pixels in y direction

-------------------------------------------------------------------------*/
void SpacialTransform(float **data, int xsize, int ysize)
{
	int xcount, ycount;
	float temp;
	for (ycount = 0; ycount < ysize; ycount++)
	{
		for (xcount = 0; xcount < xsize; xcount++)
		{
			temp = data[ycount][xcount] * powf(-1, xcount + ycount);
			data[ycount][xcount] = temp;
		}
	}
}
/*-------------------- four2()-------------------------------------

PURPOSE
Take fourier transform of 2D array

Inputs:
-data:	2D array to be input
-xsize:	number of pixels in x direction
-ysize: number of pixels in y direction
-isign: inverse or forwards
-real:	2D array to hold real component of 2DFFT
-imag:	2D array to hold imaginary component of 2DFFT
-------------------------------------------------------------------------*/
void four2(float **data, int xsize, int ysize, int isign, float **real, float **imag)
{
	int xcount, ycount;
	// Forwards Transform
	if (isign > 0)
	{
		int xcount, ycount;
		float temp;
		for (ycount = 0; ycount < ysize; ycount++)
		{
			for (xcount = 0; xcount < xsize; xcount++)
			{
				temp = data[ycount][xcount] * powf(-1, xcount + ycount);
				data[ycount][xcount] = temp;
			}
		}
		// FFT of rows
		float *horzLine;			// Each row to be transformed
		horzLine = malloc(sizeof(float)*xsize * 2);
		for (ycount = 0; ycount < ysize; ycount++)
		{
			for (xcount = 0; xcount < xsize * 2; xcount++)
			{
				horzLine[xcount] = 0;
			}
			for (xcount = 0; xcount < xsize * 2; xcount += 2)
			{
				horzLine[xcount] = data[ycount][xcount / 2];
			}

			four1(horzLine - 1, xsize, isign);

			for (xcount = 0; xcount < xsize * 2; xcount++)
			{
				data[ycount][xcount] = horzLine[xcount];
			}
		}
		
		// FFT of columns
		float *vertLine;
		vertLine = malloc(sizeof(float)*ysize * 2);
		for (xcount = 0; xcount < xsize; xcount++)
		{
			for (ycount = 0; ycount < ysize * 2; ycount++)
			{
				vertLine[ycount] = 0;
			}
			for (ycount = 0; ycount < ysize * 2; ycount += 2)
			{
				vertLine[ycount] = data[ycount / 2][xcount * 2];
				vertLine[ycount + 1] = data[ycount / 2][xcount * 2 + 1];
			}

			four1(vertLine - 1, ysize, isign);

			for (ycount = 0; ycount < ysize * 2; ycount++)
			{
				data[ycount][xcount] = vertLine[ycount];
			}
			for (ycount = 0; ycount < ysize*2; ycount+=2)
			{
				real[ycount / 2][xcount] = vertLine[ycount];
				imag[ycount / 2][xcount] = vertLine[ycount + 1];
			}
		}
		GetSpectrum(data, real, imag, xsize, ysize);
		NormalizeArray(data, xsize, ysize);
	}
	// Inverse Transform
	else
	{
		for (ycount = 0; ycount < ysize; ycount++)
		{
			for (xcount = 0; xcount < xsize * 2; xcount += 2)
			{
				data[ycount][xcount] = real[ycount][xcount / 2];
				data[ycount][xcount + 1] = imag[ycount][xcount / 2];
			}
		}
		float *vertLine;
		vertLine = malloc(sizeof(float)*ysize * 2);
		for (xcount = 0; xcount < xsize*2; xcount+=2)
		{
			for (ycount = 0; ycount < ysize * 2; ycount += 2)
			{
				vertLine[ycount] = data[ycount / 2][xcount];
				vertLine[ycount + 1] = data[ycount / 2][xcount + 1];
			}

			four1(vertLine - 1, ysize, isign);

			for (ycount = 0; ycount < ysize * 2; ycount+=2)
			{
				data[ycount/2][xcount] = vertLine[ycount];
				data[ycount / 2][xcount + 1] = vertLine[ycount+ 1];
			}
		}
		float *horzLine;			// Each row to be transformed
		horzLine = malloc(sizeof(float)*xsize * 2);
		for (ycount = 0; ycount < ysize; ycount++)
		{
			for (xcount = 0; xcount < xsize * 2; xcount ++)
			{
				horzLine[xcount] = data[ycount][xcount];
			}

			four1(horzLine - 1, xsize, isign);

			for (xcount = 0; xcount < xsize * 2; xcount++)
			{
				data[ycount][xcount] = horzLine[xcount];
			}
		}
		for (int ycount = 0; ycount < ysize; ycount++) {
			for (int xcount = 0; xcount < xsize; xcount++) {
				real[ycount][xcount] = data[ycount][xcount*2];
				imag[ycount][xcount] = data[ycount][xcount*2+1];
			}
		}
		SpacialTransform(real, xsize, ysize);
		SpacialTransform(imag, xsize, ysize);
		GetSpectrum(data, real, imag, xsize, ysize);
		NormalizeArray(data, xsize, ysize);
	}

}


/*-------------------- Butterworth()-------------------------------------

PURPOSE
Applies a butterworth filter to input 2D array

INPUT PARAMETERS
-data:	2D array to be input
-xsize:	size of array in x direction
-ysize: size of array in y direction
-real:	2D array of real numbers
-imag:	2D array of imaginary numbers
--------------------------------------------------------------------*/
void Butterworth(float **data, float **real, float **imag, int xsize, int ysize, float power)
{
	int i, j;
	float cutoff = 2;
	float filter = 0;
	float distPixel = 0;
	float **bFilter = (float **)malloc(sizeof(float *) * ysize);
	for (i = 0; i < ysize; i++)
	{
		bFilter[i] = (float *)malloc(sizeof(float) * xsize);
	}
	for (i = 0; i < ysize; i++)
	{
		for (j = 0; j < xsize; j++)
		{
			bFilter[i][j] = 1;
		}
	}
	for (i = 0; i < ysize; i++)
	{
		for (j = 0; j < xsize; j++)
		{
			distPixel = sqrt(pow(i - ysize / 2, 2) + pow(j - xsize / 2, 2));
			filter = 1 / (1 + pow(distPixel / cutoff, 2 * power));
		}
	}
	for (i = 0; i < ysize; i++)
	{
		for (j = 0; j < xsize; j++)
		{
			real[i][j] *= bFilter[i][j];
			imag[i][j] *= bFilter[i][j];
		}
	}
	GetSpectrum(data, real, imag, xsize, ysize);
	
}
