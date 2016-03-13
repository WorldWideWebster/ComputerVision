#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

void SWAP(void *a, void *b)
{
	void *tempr = a;
	a=b;
	b=tempr;
}

static char test[512][512];

/*------------------------------------------------------------------

Inputs:
-data:	array to be input
-nn:	size of array
-isign: inverse or forwards
--------------------------------------------------------------------*/

void four1(float *data, int nn, int isign, int isComplex)
{
        int n,mmax,m,j,istep,i;
        double wtemp,wr,wpr,wpi,wi,theta;
        float tempr,tempi;							// Temp real, temp imaginary
        if(!isComplex) 
			n=nn << 1;									// Multiply nn by 2, for complex
		else 
			n=nn;
		j=1;
		// Bit reversal
		for (i=1;i<n;i+=2) 
		{
				if (j > i) 
				{
						SWAP(&data[j],&data[i]);
						SWAP(&data[j+1],&data[i+1]);
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
				wtemp = sin(0.5*theta);
				wpr = -2.0*wtemp*wtemp;
				wpi= sin(theta);								
				wr=1.0;										// Real component
				wi=0.0;										// Imaginary Component
				for (m=1;m<mmax;m+=2) 
				{
						for (i=m;i<=n;i+=istep) 
						{
							printf("%u %f %f \n", j, data[j], data[j+1]);
								j=i+mmax;
								tempr=wr*data[j]-wi* data[j+1];
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
 
-------------------------------------------------------------------------*/
void four2(unsigned char ***data, int nx, int ny,int isign)
{
	int i;

	for (i=0;i<ny;i++) 
	{
		//four1((float*)test[i], nx, isign, 0);
		four1((float*)data[i]-1, nx*2, isign, 0);
	}

}

void ReadIntoArray(char *fn,int xsize, int ysize, unsigned char ***data_ptr)
{
	int i, j, k;	
    FILE *fp_inp;		
    unsigned char pixel;
    
    // Declare data as a 2D pointer array
    unsigned char **data;
    data = (unsigned char **) malloc(sizeof(unsigned char *) * ysize*2);
    for(i = 0; i < ysize; i++)
    {
		data[i] = (unsigned char *)  malloc(sizeof(unsigned char) * xsize*2);
	}
	
	// Read image contents into 2D array
    if ((fp_inp=fopen(fn,"r")) == NULL) exit(0);
	for (j = 0; j < ysize; j++)
	{
		for (k = 0; k < xsize; k++)
		{
			fread(&pixel, sizeof(char), 1, fp_inp);
			data[j][k] = pixel;
			test[j][k] = pixel;
		}
	}   
	
    (void)fclose(fp_inp);
    *data_ptr = data;
}
    
void WriteIntoArray(char *fn, char* out, int xsize, int ysize, unsigned char ***data_ptr)
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
			fwrite(data_ptr[j][k], sizeof(char), 1, out_file);
		}
	}  
}
int main()
{
	unsigned char **data;

	
	// Image mri = ImageInit("mri", 256, 256);

	ReadIntoArray("mri", 256, 256, &data);
	
	//unsigned char **spectrum = data;

	/* call the FFT routine; note the 1-0ffset for num recipes */
	four2(&data, 256, 256, 1);

	WriteIntoArray("mri", "_four", 256, 256, &data);
	
	free(data);
	//free(spectrum);

	return 0;
}

