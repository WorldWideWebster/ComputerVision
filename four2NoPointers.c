#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define SWAP(a,b) tempr=(a);(a)=(b);(b)=tempr

static char test[512][512];

/*------------------------------------------------------------------

Inputs:
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

/*-------------------------------------------------------------------------

-------------------------------------------------------------------------*/
void four2(float **data, int nx, int ny, int isign, float **real, float **imag)
{
	int i, xcount, ycount;

	// FFT of rows
	for (i = 0; i<ny; i++)
	{
		four1(data[i] - 1, nx, isign);
	}

	// FFT of columns
	float *vertLine = malloc(sizeof(float)*ny * 2);
	for (xcount = 0; xcount < nx * 2; xcount++)
	{
		for (ycount = 0; ycount < ny * 2; ycount += 2)
		{
			printf("%u", &xcount);
			vertLine[ycount] = data[ycount / 2][xcount * 2];
			vertLine[ycount + 1] = data[ycount / 2][xcount * 2 + 1];
		}
		four1(vertLine - 1, ny, 1);
		for (ycount = 0; ycount < ny * 2; ycount += 2)
		{
			real[ycount / 2][xcount] = vertLine[ycount];
			imag[ycount / 2][xcount] = vertLine[ycount + 1];
		}
	}

	// get Spectrum
	float magnitude;
	for (ycount = 0; ycount < nx; ycount++)
	{
		for (xcount = 0; xcount < ny; xcount++)
		{
			magnitude = sqrt(powf(real[ycount][xcount], 2) + powf(imag[ycount][xcount], 2));
			data[ycount][xcount] = magnitude;
		}
	}
}


void ReadIntoArray(char *fn, int xsize, int ysize, float **data)
{
	int j, k;
	FILE *fp_inp;
	unsigned char pixel;

	// Read image contents into 2D array
	if ((fp_inp = fopen(fn, "r")) == NULL) exit(0);
	for (j = 0; j < ysize; j++)
	{
		for (k = 0; k < xsize; k++)
		{
			fread(&pixel, sizeof(char), 1, fp_inp);
			data[j][k] = (float)pixel;
		}
	}

	(void)fclose(fp_inp);
}

void WriteIntoArray(char *fn, char* out, int xsize, int ysize, float **data_ptr)
{
	int j, k;
	FILE *out_file;
	char out_name[20];
	char name[15];
	strcpy(name, fn);
	strcpy(out_name, name);
	strcat(out_name, out);
	out_file = fopen(out_name, "w");
	for (j = 0; j < ysize; j++)
	{
		for (k = 0; k < xsize; k++)
		{
			fwrite((unsigned char)data_ptr[j][k], sizeof(char), 1, out_file);
		}
	}
}
int main()
{
	int i;
	int ysize = 256;
	int xsize = 256;
	float **data;
	data = (float **)malloc(sizeof(float *) * ysize * 2);
	for (i = 0; i < ysize * 2; i++)
	{
		data[i] = (float *)malloc(sizeof(float) * xsize * 2);
	}

	// Image mri = ImageInit("mri", 256, 256);

	ReadIntoArray("mri", 256, 256, data);

	float **spectrum = data;
	float **real = (float **)malloc(sizeof(float *) * ysize);
	for (i = 0; i < ysize; i++)
	{
		real[i] = (float *)malloc(sizeof(float) * xsize);
	}
	float **imag = real;


	/* call the FFT routine; note the 1-0ffset for num recipes */
	four2(spectrum, 256, 256, 1, real, imag);

	WriteIntoArray("mri", "_spectrum", 256, 256, spectrum);

	free(data);
	free(spectrum);
	free(real);
	free(imag);

	return 0;
}

