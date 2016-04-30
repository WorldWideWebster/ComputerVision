/*--------------- arrays.h ---------------

by:   Sean Webster

PURPOSE
function prototypes for arrays.c

---------------------------------------------*/

#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h> 

#ifndef ARRAYS_H
#define ARRAYS_H

float **ImageInit(int xsize, int ysize);
int OpenImage(char *fn, int xsize, int ysize, float **data);
void SaveImage(char *fn, char* out, int xsize, int ysize, float **data_ptr);
void SaveImageAsText(float *fn, char* out, int xsize, int ysize, float **data_ptr);
void AccuracyReport(float **image1, float **image2, int xsize, int ysize);

#endif