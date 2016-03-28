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

void ReadIntoArray(char *fn, int xsize, int ysize, unsigned char **data);
void WriteIntoArray(char *fn, char* out, int xsize, int ysize, float **data_ptr);
void NormalizeArray(float **data, int xsize, int ysize);


#endif