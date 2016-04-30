/*--------------- Circles.c ---------------
PURPOSE: Creates Circles

by:		Sean Webster
		Computer Vision
		Due 4/4/2016
---------------------------------------------*/

#include "Circles.h"
/*-------------------- CreateCircle()-------------------------------------

PURPOSE
Creates a circle in image

INPUT PARAMETERS
-inData:	old 2D array to be input
-outData:	new 2D array to be input
-xsize:		size of array in x direction
-ysize:		size of array in y direction
-xloc:		x location of circle
-yloc:		y location of circle
-intensity:	intensity of circle
-radius:	radius of circle
--------------------------------------------------------------------*/
void CreateCircle(float **data, int ysize, int xsize, int xloc, int yloc, int intensity, int rad)
{
	int x, y;
	for (y = 0; y < ysize; y++)
	{
		for (x = 0; x < xsize; x++)
		{
			if (pow(x - xloc, 2) + pow(y - yloc, 2) - pow(rad, 2) <= 0)
				data[y][x] += intensity;
		}
	}
}