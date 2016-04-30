/*--------------- HW3.c ---------------

by:		Sean Webster
		Computer Vision
		Due 4/4/2016

---------------------------------------------*/

#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "arrays.h"
#include "Spacial.h"
#include "Circles.h"

int main()
{
	/*----------------------------Part 1------------------------------------*/
	int ysize = 342;
	int xsize = 546;
	int padding = 1;


	float	**inImage = ImageInit(xsize, ysize);
	float	**padImage = ImageInit(xsize + 2*padding, ysize + 2*padding);
	float	**sobelImage = ImageInit(xsize, ysize);
	float	**threshImage = ImageInit(xsize, ysize);

	
	OpenImage("porsche", xsize, ysize, inImage);
	PadImage(inImage, padImage, xsize, ysize, padding);
	Sobel(padImage, sobelImage, xsize + 2*padding, ysize + 2*padding);
	SaveImage("porsche", "_sobel", xsize, ysize, sobelImage);
	BinThresh(sobelImage, threshImage, xsize, ysize, 60);
	SaveImage("porsche", "_thresh60", xsize, ysize, threshImage);


	ysize = 256;
	xsize = 256;
	OpenImage("mri", xsize, ysize, inImage);
	PadImage(inImage, padImage, xsize, ysize, padding);
	Sobel(padImage, sobelImage, xsize + 2 * padding, ysize + 2 * padding);
	SaveImage("mri", "_sobel", xsize, ysize, sobelImage);
	BinThresh(sobelImage, threshImage, xsize, ysize, 50);
	SaveImage("mri", "_thresh50", xsize, ysize, threshImage);

	free(inImage);
	free(padImage);
	free(sobelImage);
	free(threshImage);

	/*----------------------------Part 2------------------------------------*/
	xsize = ysize = 256;
	float	**circImage = ImageInit(xsize, ysize);
	float	**padCirc = ImageInit(xsize + 2 * padding, ysize + 2 * padding);
	float	**sobelCirc = ImageInit(xsize, ysize);
	float	**threshCirc = ImageInit(xsize, ysize);
	float	**noiseCirc = ImageInit(xsize, ysize);
	float	**padNoiseCirc = ImageInit(xsize + 2 * padding, ysize + 2 * padding);
	float	**sobelNoiseCirc = ImageInit(xsize, ysize);
	float	**noiseGaussCirc = ImageInit(xsize, ysize);
	float	**padNoiseGaussCirc = ImageInit(xsize + 2 * padding, ysize + 2 * padding);
	float	**sobelNoiseGaussCirc = ImageInit(xsize, ysize);
	float	**sobelNoiseGaussThreshCirc = ImageInit(xsize, ysize);

	float **test = ImageInit(xsize + 2, ysize +2);

	int c = 256 / 2 - 1;
	CreateCircle(circImage, ysize, xsize, c, c, 50, 60);
	CreateCircle(circImage, ysize, xsize, c, c, 50, 40);
	CreateCircle(circImage, ysize, xsize, c, c, 50, 20);


	SaveImage("circles", "", xsize, ysize, circImage);
	PadImage(circImage, padCirc, xsize, ysize, padding);
	Sobel(padCirc, sobelCirc, xsize + 2 * padding, ysize + 2 * padding);
	SaveImage("circles", "_sobel", xsize, ysize, sobelCirc);

	BinThresh(sobelCirc, threshCirc, xsize, ysize, 100);
	SaveImage("circles", "_thresh100", xsize, ysize, threshCirc);

	// Noise = 10
	AddUniNoise(circImage, noiseCirc, xsize, ysize, 10);
	SaveImage("circles", "_noise10", xsize, ysize, noiseCirc);

	PadImage(noiseCirc, padNoiseCirc, xsize, ysize, padding);
	Sobel(padNoiseCirc, sobelNoiseCirc, xsize + 2 * padding, ysize + 2 * padding);
	BinThresh(sobelNoiseCirc, sobelNoiseCirc, xsize, ysize, 100);
	SaveImage("circles", "_noise_sobel10", xsize, ysize, sobelNoiseCirc);
	AccuracyReport(threshCirc, sobelNoiseCirc, xsize, ysize);

	GaussianSmooth(padNoiseCirc, noiseGaussCirc, xsize + 2 * padding, ysize + 2 * padding);
	SaveImage("circles", "_noise_gauss10", xsize, ysize, noiseGaussCirc);
	PadImage(noiseGaussCirc, padNoiseGaussCirc, xsize, ysize, padding);
	Sobel(padNoiseGaussCirc, sobelNoiseGaussCirc, xsize + 2 * padding, ysize + 2 * padding);
	BinThresh(sobelNoiseGaussCirc, sobelNoiseGaussThreshCirc, xsize, ysize, 100);
	SaveImage("circles", "_noise_sobel_gauss_thresh10", xsize, ysize, sobelNoiseGaussThreshCirc);
	AccuracyReport(threshCirc, sobelNoiseGaussThreshCirc, xsize, ysize);

	// Noise = 50
	AddUniNoise(circImage, noiseCirc, xsize, ysize, 50);
	SaveImage("circles", "_noise50", xsize, ysize, noiseCirc);

	PadImage(noiseCirc, padNoiseCirc, xsize, ysize, padding);
	Sobel(padNoiseCirc, sobelNoiseCirc, xsize + 2 * padding, ysize + 2 * padding);
	BinThresh(sobelNoiseCirc, sobelNoiseCirc, xsize, ysize, 100);
	SaveImage("circles", "_noise_sobel50", xsize, ysize, sobelNoiseCirc);
	AccuracyReport(threshCirc, sobelNoiseCirc, xsize, ysize);

	GaussianSmooth(padNoiseCirc, noiseGaussCirc, xsize + 2 * padding, ysize + 2 * padding);
	SaveImage("circles", "_noise_gauss50", xsize, ysize, noiseGaussCirc);
	PadImage(noiseGaussCirc, padNoiseGaussCirc, xsize, ysize, padding);
	Sobel(padNoiseGaussCirc, sobelNoiseGaussCirc, xsize + 2 * padding, ysize + 2 * padding);
	BinThresh(sobelNoiseGaussCirc, sobelNoiseGaussThreshCirc, xsize, ysize, 100);
	SaveImage("circles", "_noise_sobel_gauss_thresh50", xsize, ysize, sobelNoiseGaussThreshCirc);
	AccuracyReport(threshCirc, sobelNoiseGaussThreshCirc, xsize, ysize);


	// Noise = 100
	AddUniNoise(circImage, noiseCirc, xsize, ysize, 100);
	SaveImage("circles", "_noise100", xsize, ysize, noiseCirc);

	PadImage(noiseCirc, padNoiseCirc, xsize, ysize, padding);
	Sobel(padNoiseCirc, sobelNoiseCirc, xsize + 2 * padding, ysize + 2 * padding);
	BinThresh(sobelNoiseCirc, sobelNoiseCirc, xsize, ysize, 100);
	SaveImage("circles", "_noise_sobel100", xsize, ysize, sobelNoiseCirc);
	AccuracyReport(threshCirc, sobelNoiseCirc, xsize, ysize);

	GaussianSmooth(padNoiseCirc, noiseGaussCirc, xsize + 2 * padding, ysize + 2 * padding);
	SaveImage("circles", "_noise_gauss100", xsize, ysize, noiseGaussCirc);
	PadImage(noiseGaussCirc, padNoiseGaussCirc, xsize, ysize, padding);
	Sobel(padNoiseGaussCirc, sobelNoiseGaussCirc, xsize + 2 * padding, ysize + 2 * padding);
	BinThresh(sobelNoiseGaussCirc, sobelNoiseGaussThreshCirc, xsize, ysize, 100);
	SaveImage("circles", "_noise_sobel_gauss_thresh100", xsize, ysize, sobelNoiseGaussThreshCirc);
	AccuracyReport(threshCirc, sobelNoiseGaussThreshCirc, xsize, ysize);


	free(circImage);
	free(padCirc);
	free(sobelCirc);
	free(threshCirc);
	free(noiseCirc);
	free(padNoiseCirc);
	free(sobelNoiseCirc);
	free(noiseGaussCirc);
	free(padNoiseGaussCirc);
	free(sobelNoiseGaussCirc);
	free(sobelNoiseGaussThreshCirc);

	return 0;
}

