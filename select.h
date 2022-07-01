#pragma once

#include "image_editor.h"

#define NUMCIF 100

// function to select a given portion(by coordinates) from an image/matrix
void selecting(char **parameters, image * imag, int *selected);

// function to select the full image/matrix
void selecting_all(image *imag, int *selected_all);
