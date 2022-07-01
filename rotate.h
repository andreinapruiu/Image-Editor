#pragma once

#include "image_editor.h"
#include "crop.h"

// function to rotate a grayscale matrix based on the
// current selection at a given angle
void rotate_noncolor(image * imag);

// function to rotate a full matrix at a given angle
void rotate_noncolor_all(image *imag);

// function to swap different types
void swap_rgb(pixels *x, pixels *y);

void swap(double *x, double *y);

// same as rotate_noncolor, but with rgb image
void rotate_rgb(image *imag);

// same as rotate_noncolor_all, but with rgb image
void rotate_rgb_all(image *imag);

// function that uses the other function to rotate any image or a given portion
// at a given angle
void rotate_any(image *imag, char **parameters,
				int loaded, int loaded_rgb, int *rotated);
