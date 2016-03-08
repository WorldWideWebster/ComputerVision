/* sample.c
/*
/* The enclosed function reads in a one-byte/pixel unsigned char image */
/* with filename in variable fn, and of size xsize*ysize  */ 
/* the array data is declared with the statement:    */ 
/* data=(unsigned char*)calloc(xsize*ysize, sizeof(char));*/ 
/* upon exiting cdatainput, data will contain the input image */ 
#include <stdio.h>
#include <stdlib.h>



void cdatainput(char *fn,int xsize, int ysize, unsigned char *data)

{
    int i;
	int j;
    FILE *fp_inp;
    unsigned char pixel;
    unsigned char max, min;
	unsigned char thedata[256][256];
    max=0;
    min=255;

    if ((fp_inp=fopen(fn,"r")) == NULL) exit(0);
    for (i=0; i<ysize; i++) 
        {
			for (j=0; j<xsize; j++) 
			{
				fread(&pixel, sizeof(char),1,fp_inp);

				thedata[i][j] = pixel;


			}
	}



(void)fclose(fp_inp);
printf("Max and min of image are: %d %d \n", (int)max, (int)min);

}

