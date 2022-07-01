#pragma once

#include "image_editor.h"
#include "crop.h"

// function to round the rgb pixels to their maximum or minimum extent
double clamp_double(double x);

// the function below have the same purpose, to fo their effect
void apply_edge(image *imag, pixels **aux);

void apply_sharpen(image *imag, pixels **aux);

void apply_blur(image *imag, pixels **aux);

void apply_gaussianblur(image *imag, pixels **aux);

// function that uses the other to apply an effect to an image or
// to a selected portion of an image
void apply_any(char **parameters, image *imag, int *applied);
