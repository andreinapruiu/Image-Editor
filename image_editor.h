#pragma once

#define COMSIZE 40
#define MAXPAR 4
#define MAXCOM 5

// struct for a coordinate point
typedef struct coordinates {
	int x;
	int y;
} coords;

// struct for a pixel as rgb color
typedef struct pixels {
	double red;
	double green;
	double blue;
} pixels;

// struct for the image itself in the specified format(ppm, pgm)
typedef struct image {
	char magic_number[2];
	int width;
	int height;
	unsigned int maxval;
	double **matrix;
	pixels **matrix_rgb;
	coords start;
	coords end;
} image;

// enum to use the commands as they are(SAVE, LOAD, not numbers)
typedef enum commands {
	NO,
	LOAD,
	SELECT,
	SELECT_ALL,
	ROTATE,
	CROP,
	APPLY,
	SAVE,
	EXIT
} commands;
