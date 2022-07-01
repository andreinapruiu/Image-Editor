#pragma once

#include "image_editor.h"

#define MAXLINE 500

// function to free a matrix
void free_matrix(double **a, int nl);

// function to allocate a matrix
double **alloc_matrix(int nc, int nl);

// function to free a matrix that has rgb colors
void free_matrix_rgb(pixels **a, int nl);

// function to allocate a matrix that has rgb colors
pixels **alloc_matrix_rgb(int nc, int nl);

// function that skips the comments between the start of the file and
// the character '#' or between 2 '#'
void skip_comments(FILE *in);

// function to verify if a matrix is correctly allocated
void noncolor(FILE *in, image *imag);

// function to read the matrix contents from an ascii file
void read_ascii(FILE *in, image *imag);

// all the function below have the same purpose: to read the data
// from the file as it should be done based on the magic number
void solve_P1(FILE *in, image *imag, int *loaded);

void solve_P2(FILE *in, image *imag, int *loaded);

void solve_P4(FILE *in, image *imag, char **parameters, int *loaded);

void solve_P5(FILE *in, image *imag, char **parameters, int *loaded);

void solve_P3(FILE *in, image *imag, int *loaded_rgb);

void solve_P6(FILE *in, image *imag, char **parameters, int *loaded_rgb);

// the main function for load
void load_any(char **parameters, image *imag, int *loaded, int *loaded_rgb);
