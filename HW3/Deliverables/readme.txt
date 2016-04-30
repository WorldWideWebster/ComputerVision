Sean Webster

Homework 3 readme


Source Code Files
	HW3.c
	arrays.c
	Spacial.c
	Circles.c

Header Files
	arrays.h
	Spacial.h
	Circles.h

Executables
	HW3
	
Instructions for running
	Run program, then convert images out of raw format

Inputs
	mri			256 x 256	65.5 KB
	Porsche			546 x 342	183  KB

Outputs
	mri_sobel		256 x 256	65.5 KB
	mri_thresh50		256 x 256	65.5 KB
	porsche_sobel		546 x 342	183  KB
	porsche_thresh60	546 x 342	183  KB
	circles			256 x 256	64   KB
	circles_sobel		256 x 256	64   KB
	circles_thresh100	256 x 256	64   KB
	circles_noise10		256 x 256	64   KB
	circles_noise50		256 x 256	64   KB
	circles_noise100	256 x 256	64   KB
	circles_noise_gauss10	256 x 256	64   KB
	circles_noise_gauss50	256 x 256	64   KB
	circles_noise_gauss100	256 x 256	64   KB
	circles_noise_gauss_thresh10	256 x 256	64   KB
	circles_noise_gauss_thresh50	256 x 256	64   KB
	circles_noise_gauss_thresh100	256 x 256	64   KB
XV Commands
	(echo P5; echo 256 256; echo 255; cat mri_sobel) xv -
	(echo P5; echo 256 256; echo 255; cat mri_thresh50) xv -
	(echo P5; echo 546 342; echo 255; cat porsche_sobel) xv -
	(echo P5; echo 546 342; echo 255; cat porsche_thresh60) xv -
	(echo P5; echo 256 256; echo 255; cat circles) xv -
	(echo P5; echo 256 256; echo 255; cat circles_sobel) xv -
	(echo P5; echo 256 256; echo 255; cat circles_thresh100) xv -
	(echo P5; echo 256 256; echo 255; cat circles_noise10) xv -
	(echo P5; echo 256 256; echo 255; cat circles_noise50) xv -
	(echo P5; echo 256 256; echo 255; cat circles_noise100) xv -
	(echo P5; echo 256 256; echo 255; cat circles_noise_gauss10) xv -
	(echo P5; echo 256 256; echo 255; cat circles_noise_gauss50) xv -
	(echo P5; echo 256 256; echo 255; cat circles_noise_gauss100) xv -
	(echo P5; echo 256 256; echo 255; cat circles_noise_gauss_thresh10) xv -
	(echo P5; echo 256 256; echo 255; cat circles_noise_gauss_thresh50) xv -
	(echo P5; echo 256 256; echo 255; cat circles_noise_gauss_thresh100) xv -
