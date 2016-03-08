#include <math.h>
#include <stdlib.h>
#include <stdio.h>

#define SWAP(a,b) tempr=(a);(a)=(b);(b)=tempr


/*------------------------------------------------------------------

Inputs:
-data:	array to be input
-nn:	size of array
-isign: inverse or forwards
--------------------------------------------------------------------*/

void four1(&data, nn, isign)
float data[];
int nn,isign;
{
        int n,mmax,m,j,istep,i, x;
        double wtemp,wr,wpr,wpi,wi,theta;
        float tempr,tempi;							// Temp real, temp imaginary
        n=nn << 1;									// Multiply nn by 2, for complex
		j=1;
		// Bit reversal
		for (i=1;i<n;i+=2) 
		{
				if (j > i) 
				{
						SWAP(data[j],data[i]);
						SWAP(data[j+1],data[i+1]);
				}
				m=n >> 1;
				while (m >= 2 && j > m) 
				{
						j -= m;
						m >>= 1;
				}
				j += m;
		}
		// Compute FFT
		mmax=2;
		while (n > mmax) 
		{
				istep=2*mmax;
				theta=6.28318530717959/(isign*mmax);		//2 pi radians / isign*mmax
				wtemp=sin(0.5*theta);
				wpr = -2.0*wtemp*wtemp;
				wpi=sin(theta);								
				wr=1.0;										// Real component
				wi=0.0;										// Imaginary Component
				for (m=1;m<mmax;m+=2) 
				{
						for (i=m;i<=n;i+=istep) 
						{
								j=i+mmax;
								tempr=wr*data[j]-wi*data[j+1];
								tempi=wr*data[j+1]+wi*data[j];
								data[j]=data[i]-tempr;
								data[j+1]=data[i+1]-tempi;
								data[i] += tempr;
								data[i+1] += tempi;
						}
						wr=(wtemp=wr)*wpr-wi*wpi+wr;
						wi=wi*wpr+wtemp*wpi+wi;
				}
				mmax=istep;
		}
	// Scaling for forward transform 
	if (isign == 1) 
	{
      for (i=0;i<nn;i++) 
	  {
         data[i] /= (double)nn;
      }
	}
        
}

/*-------------------------------------------------------------------------
 
*/
int FFT2D(COMPLEX **data,int nx,int ny,int isign)
{
   int i,j;
   double *real,*imag;

   /* Transform the rows */
   real = (double *)malloc(nx * sizeof(double));
   imag = (double *)malloc(nx * sizeof(double));

   for (j=0;j<ny;j++) {
      for (i=0;i<nx;i++) {
		if(j % 2 == 0)
			real[i] = c[i][j];
		else
			imag[i] = c[i][j];
      }
      four1(data, nx, isign);
      for (i=0;i<nx;i++) {
		  if(j % 2 == 0)
			c[i][j] = real[i];
		  else
			c[i][j] = imag[i];
      }
   }
   free(real);
   free(imag);

   /* Transform the columns */
   real = (double *)malloc(ny * sizeof(double));
   imag = (double *)malloc(ny * sizeof(double));

   for (i=0;i<nx;i++) {
      for (j=0;j<ny;j++) {
		if(j % 2 == 0)
			real[i] = c[i][j];
		else
			imag[i] = c[i][j];
      }
      four1(data, ny, isign);
      for (j=0;j<ny;j++) {
		  if(j % 2 == 0)
			c[i][j] = real[i];
		  else
			c[i][j] = imag[i];
      }
   }
   free(real);
   free(imag);
}

int main ()
{
int i, j, n;
float *data, *spectrum, *output;

n=8;

/* 3 arrays with the following meaning */
/* data -->FFT --> spectrum --> IFFT --> output */
data =(float *) calloc (2*n, sizeof (float));
spectrum = (float *) calloc (2*n, sizeof (float));
output = (float *) calloc (2*n, sizeof (float));

/* setup data array: first init everything to O's */
for (i=0; i<2*n; i++)
	data[i]= 0.0;
data[6] = 0.5;
data[8] =1.0;
data[10]= 0.5;

 /* since fourl destroys the input array with the output */
/* use the output of the FFT as the input value */
for (i=0; i<2*n; i++)
	spectrum[i] = data[i];

/* call the FFT routine; note the 1-0ffset for num recipes */
four1(spectrum-1, n, 1);

/*copy spectrum into output and call invcrse FFT */
for (i=0; i<2*n; i++)
output[i] = spectrum[i];

/* IFFT call, with a zero-offset array */
four1(output-1, n, -1);

/* outputs */
/* printf (“Outputs \n”);*/
for (i=0; i<2*n; i++) {
printf ("%d %f %f %f \n", i, data[i], spectrum[i], output[i]/n);
}

return 0;
}

