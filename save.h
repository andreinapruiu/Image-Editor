#pragma once

#include "image_editor.h"

// function to change a magic number with its correspond binary magic number
void change_magic_ascii(FILE * out, image imag);

// function to do the reverse of the above
void change_magic_bin(FILE *out, image imag);

// function to save the data in ascii format
void save_ascii(FILE *out, image imag);

// function to save the data in binary format
void save_bin(FILE *out_bin, image imag);

// main function that uses the other functions to save a file
void save_any(char **parameters, image imag,
			  int loaded, int loaded_rgb, int *saved);
