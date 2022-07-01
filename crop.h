#pragma once

#include "image_editor.h"

// function to create a redimension of the inital matrix by cropping
// the active selection from the original file
double **redimension_matrix(double **a, int start_x, int start_y,
							int end_x, int end_y, int nl_a);

// function to crop a grayscale image
void crop_noncolor(image *imag);

// function to crop a rgb image
void crop_rgb(image *imag);

// function that uses the other functions to crop any file given at input
void crop_any(image *imag, int loaded, int loaded_rgb, int *cropped);
