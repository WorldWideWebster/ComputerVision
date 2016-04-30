/*--------------- filtering.h ---------------

by:   Sean Webster

PURPOSE
function prototypes for filtering.c

---------------------------------------------*/

#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h> 
#include "arrays.h"

#ifndef FILTERING_H
#define FILTERING_H
//----- f u n c t i o n    p r o t o t y p e s
#define SWAP(a,b) tempr=(a);(a)=(b);(b)=tempr
void four1(float *data, int nn, int isign);
void GetSpectrum(float **data, float **real, float **imag, int xsize, int ysize);
void iFour2Prep(float **data, float **real, float **imag, int xsize, int ysize);
void SpacialTransform(float **data, int xsize, int ysize);
void four2(float **data, int xsize, int ysize, int isign, float **real, float **imag);
void Butterworth(float **data, float **real, float **imag, int xsize, int ysize, float power);

#endif