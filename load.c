#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "image_editor.h"
#include "load.h"

void free_matrix(double **a, int nl)
{
	for (int i = 0; i < nl; i++)
		free(a[i]);

	free(a);
}

double **alloc_matrix(int nc, int nl)
{
	double **a;

	a = malloc(nl * sizeof(double *));
	if (!a)
		return NULL;

	for (int i = 0; i < nl; i++) {
		a[i] = malloc(nc * sizeof(double));
		if (!a[i]) {
			free_matrix(a, i);
			return NULL;
		}
	}

	return a;
}

void free_matrix_rgb(pixels **a, int nl)
{
	for (int i = 0; i < nl; i++)
		free(a[i]);

	free(a);
}

pixels **alloc_matrix_rgb(int nc, int nl)
{
	pixels **a;

	a = malloc(nl * sizeof(pixels *));
	if (!a)
		return NULL;

	for (int i = 0; i < nl; i++) {
		a[i] = malloc(nc * sizeof(pixels));
		if (!a[i]) {
			free_matrix_rgb(a, i);
			return NULL;
		}
	}

	return a;
}

void skip_comments(FILE *in)
{
	char c;

	fscanf(in, "%c", &c);

	while (c == '#') {
		while (c != '\n')
			fscanf(in, "%c", &c);
		fscanf(in, "%c", &c);
	}
	fseek(in, -1, SEEK_CUR);
}

void noncolor(FILE *in, image *imag)
{
	imag->matrix = alloc_matrix(imag->width, imag->height);

	if (!imag->matrix) {
		fprintf(stderr, "Failed allocation\n");
		fclose(in);
		exit(-1);
	}
}

void read_ascii(FILE *in, image *imag)
{
	for (int i = 0; i < imag->height; i++)
		for (int j = 0; j < imag->width; j++)
			fscanf(in, "%lf", &imag->matrix[i][j]);
}

void read_bin(FILE *in_bin, image *imag)
{
	for (int i = 0; i < imag->height; i++)
		for (int j = 0; j < imag->width; j++) {
			unsigned char aux;
			fread(&aux, sizeof(unsigned char), 1, in_bin);
			imag->matrix[i][j] = aux;
		}
}

void solve_P1(FILE *in, image *imag, int *loaded)
{
	noncolor(in, imag);
	read_ascii(in, imag);
	(*loaded) = 1;

	fclose(in);
}

void solve_P2(FILE *in, image *imag, int *loaded)
{
	fscanf(in, "%d", &imag->maxval);
	fseek(in, 1, SEEK_CUR);

	skip_comments(in);

	noncolor(in, imag);

	read_ascii(in, imag);

	fclose(in);

	(*loaded) = 1;
}

void solve_P4(FILE *in, image *imag, char **parameters, int *loaded)
{
	noncolor(in, imag);

	int pos = ftell(in);
	fclose(in);

	FILE *in_bin = fopen(parameters[0], "rb");
	if (!in_bin) {
		free_matrix(imag->matrix, imag->height);
		return;
	}

	fseek(in_bin, pos, SEEK_SET);

	read_bin(in_bin, imag);

	(*loaded) = 1;

	fclose(in_bin);
}

void solve_P5(FILE *in, image *imag, char **parameters, int *loaded)
{
	fscanf(in, "%d", &imag->maxval);
	fseek(in, 1, SEEK_CUR);

	skip_comments(in);

	noncolor(in, imag);

	int pos = ftell(in);
	fclose(in);

	FILE *in_bin = fopen(parameters[0], "rb");
	if (!in_bin) {
		free_matrix(imag->matrix, imag->height);
		return;
	}

	fseek(in_bin, pos, SEEK_SET);

	read_bin(in_bin, imag);

	(*loaded) = 1;

	fclose(in_bin);
}

void solve_P3(FILE *in, image *imag, int *loaded_rgb)
{
	fscanf(in, "%d", &imag->maxval);
	fseek(in, 1, SEEK_CUR);

	skip_comments(in);

	imag->matrix_rgb = alloc_matrix_rgb(imag->width, imag->height);

	if (!imag->matrix_rgb) {
		fprintf(stderr, "Failed allocation\n");
		fclose(in);
		exit(-1);
	}

	for (int i = 0; i < imag->height; i++)
		for (int j = 0; j < imag->width; j++) {
			fscanf(in, "%lf", &imag->matrix_rgb[i][j].red);
			fscanf(in, "%lf", &imag->matrix_rgb[i][j].green);
			fscanf(in, "%lf", &imag->matrix_rgb[i][j].blue);
		}

	(*loaded_rgb) = 1;

	fclose(in);
}

void solve_P6(FILE *in, image *imag, char **parameters, int *loaded_rgb)
{
	fscanf(in, "%d", &imag->maxval);
	fseek(in, 1, SEEK_CUR);

	skip_comments(in);

	int pos = ftell(in);
	fclose(in);

	imag->matrix_rgb = alloc_matrix_rgb(imag->width, imag->height);

	if (!imag->matrix_rgb) {
		fprintf(stderr, "Failed allocation\n");
		exit(-1);
	}

	FILE *in_bin = fopen(parameters[0], "rb");
	if (!in_bin) {
		free_matrix_rgb(imag->matrix_rgb, imag->height);
		return;
	}

	fseek(in_bin, pos, SEEK_SET);

	for (int i = 0; i < imag->height; i++)
		for (int j = 0; j < imag->width; j++) {
			unsigned char aux_red, aux_green, aux_blue;

			fread(&aux_red, sizeof(unsigned char), 1, in_bin);
			imag->matrix_rgb[i][j].red = aux_red;

			fread(&aux_green, sizeof(unsigned char), 1, in_bin);
			imag->matrix_rgb[i][j].green = aux_green;

			fread(&aux_blue, sizeof(unsigned char), 1, in_bin);
			imag->matrix_rgb[i][j].blue = aux_blue;
		}

	(*loaded_rgb) = 1;

	fclose(in_bin);
}

void load_any(char **parameters, image *imag, int *loaded, int *loaded_rgb)
{
	if ((*loaded) == 1) {
		free_matrix(imag->matrix, imag->height);
		(*loaded) = 0;
	}

	if ((*loaded_rgb) == 1) {
		free_matrix_rgb(imag->matrix_rgb, imag->height);
		(*loaded_rgb) = 0;
	}

	FILE *in = fopen(parameters[0], "r");

	if (!in)
		return;

	skip_comments(in);

	fgets(imag->magic_number, 5, in);

	imag->magic_number[2] = '\0';

	skip_comments(in);

	fscanf(in, "%d%d", &imag->width, &imag->height);
	fseek(in, 1, SEEK_CUR);

	skip_comments(in);

	if (!strcmp(imag->magic_number, "P1"))
		solve_P1(in, imag, loaded);
	else if (!strcmp(imag->magic_number, "P2"))
		solve_P2(in, imag, loaded);
	else if (!strcmp(imag->magic_number, "P4"))
		solve_P4(in, imag, parameters, loaded);
	else if (!strcmp(imag->magic_number, "P5"))
		solve_P5(in, imag, parameters, loaded);
	else if (strcmp(imag->magic_number, "P3") == 0)
		solve_P3(in, imag, loaded_rgb);
	else if (strcmp(imag->magic_number, "P6") == 0)
		solve_P6(in, imag, parameters, loaded_rgb);
}
