
#include <stdlib.h>
#include <stdio.h>
#include <string.h>


void ModImage(char *fn,int xsize, int ysize, unsigned char *data)

{
	// Declarations
	int j, k;
	char name[15];	
    FILE *fp_inp;
	FILE *quad_file;
	FILE *evens_file;
	char quad_name[20];
	char evens_name[20];
	unsigned char pixel;


	// Naming output files
	strcpy(name, fn);
	strcpy(quad_name, name);
	strcat(quad_name, "_quad");
	strcpy(evens_name, name);
	strcat(evens_name, "_even");
	evens_file=fopen(evens_name, "w+");
	quad_file=fopen(quad_name,"w+");

	// Output even bytes only
    if ((fp_inp=fopen(fn,"r")) == NULL) exit(0);
	for (j = 0; j<ysize; j++)
	{
		if (j % 2 == 0)
		{
			for (k = 0; k < xsize; k++)
			{
				fread(&pixel, sizeof(char), 1, fp_inp);
				if (k % 2 == 0)
					fwrite(&pixel, sizeof(char), 1, evens_file);
			}
		}
	}

	// Output left two quadrants
	for (j=0; j<ysize; j++) 
    {
		for(k=0; k<xsize; k++)
		{
			fread(&pixel, sizeof(char),1,fp_inp);
			if(k>xsize/2)
				pixel = 0;

			fwrite(&pixel, sizeof(char),1,quad_file);
		}
	}

(void)fclose(evens_file);
(void)fclose(quad_file);
(void)fclose(fp_inp);
}

int main()
{
	unsigned char *data = malloc(256*256);

	ModImage("mri", 256, 256, &data);
	system("pause");

	return 0;

}