/*--------------- Spacial.h ---------------
	
		by:   Sean Webster
	
		PURPOSE
		function prototypes for Spacial.c

---------------------------------------------*/


#include "arrays.h"
#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <float.h>


#ifndef SPACIAL_H
#define SPACIAL_H

void PadImage(float **oData, float **nData, int xsize, int ysize, int pSize);
void Sobel(float **inData, float **lineData, int xsize, int ysize);
void BinThresh(float **inData, float **outData, int xsize, int ysize, int thresh);
void AddUniNoise(float** inData, float **outData, int xsize, int ysize, int intens);
void GaussianSmooth(float **inData, float **outData, int xsize, int ysize);

#endif