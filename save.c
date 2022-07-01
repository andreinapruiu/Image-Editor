#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

#include "image_editor.h"
#include "save.h"

void change_magic_ascii(FILE *out, image imag)
{
	if (!strcmp(imag.magic_number, "P4"))
		fprintf(out, "P1\n");
	else if (!strcmp(imag.magic_number, "P5"))
		fprintf(out, "P2\n");
	else if (!strcmp(imag.magic_number, "P6"))
		fprintf(out, "P3\n");
	else
		fprintf(out, "%s\n", imag.magic_number);
}

void change_magic_bin(FILE *out, image imag)
{
	if (!strcmp(imag.magic_number, "P1"))
		fprintf(out, "P4\n");
	else if (!strcmp(imag.magic_number, "P2"))
		fprintf(out, "P5\n");
	else if (!strcmp(imag.magic_number, "P3"))
		fprintf(out, "P6\n");
	else
		fprintf(out, "%s\n", imag.magic_number);
}

void save_ascii(FILE *out, image imag)
{
	for (int i = 0; i < imag.height; i++) {
		for (int j = 0; j < imag.width; j++) {
			unsigned char aux = (unsigned char)round(imag.matrix[i][j]);
			if (j == imag.width - 1)
				fprintf(out, "%u\n", aux);
			else
				fprintf(out, "%u ", aux);
		}
	}
}

void save_bin(FILE *out_bin, image imag)
{
	for (int i = 0; i < imag.height; i++) {
		for (int j = 0; j < imag.width; j++) {
			unsigned char aux = (unsigned char)round(imag.matrix[i][j]);
			fwrite(&aux, sizeof(unsigned char), 1, out_bin);
		}
	}
}

void save_any(char **parameters, image imag,
			  int loaded, int loaded_rgb, int *saved)
{
	FILE *out = fopen(parameters[0], "w");
	if (!out) {
		fprintf(stderr, "Failed to open\n");
		return;
	}

	if (!strcmp(parameters[1], "ascii")) {
		change_magic_ascii(out, imag);
		fprintf(out, "%d %d\n", imag.width, imag.height);

		if (!strcmp(imag.magic_number, "P2") ||
			!strcmp(imag.magic_number, "P3") ||
			!strcmp(imag.magic_number, "P5") ||
			!strcmp(imag.magic_number, "P6")) {
			fprintf(out, "%d\n", imag.maxval);
		}

		if (loaded)
			save_ascii(out, imag);
		if (loaded_rgb)
			for (int i = 0; i < imag.height; i++) {
				for (int j = 0; j < imag.width; j++) {
					unsigned char aux_red =
						(unsigned char)round(imag.matrix_rgb[i][j].red);
					unsigned char aux_green =
						(unsigned char)round(imag.matrix_rgb[i][j].green);
					unsigned char aux_blue =
						(unsigned char)round(imag.matrix_rgb[i][j].blue);
					if (j == imag.width - 1)
						fprintf(out, "%u %u %u\n",
								aux_red, aux_green, aux_blue);
					else
						fprintf(out, "%u %u %u ",
								aux_red, aux_green, aux_blue);
				}
			}

		fclose(out);
	} else {
		change_magic_bin(out, imag);
		fprintf(out, "%d %d\n", imag.width, imag.height);

		if (!strcmp(imag.magic_number, "P2") ||
			!strcmp(imag.magic_number, "P3") ||
			!strcmp(imag.magic_number, "P5") ||
			!strcmp(imag.magic_number, "P6")) {
			fprintf(out, "%d\n", imag.maxval);
		}

		int pos = ftell(out);
		fclose(out);

		FILE *out_bin = fopen(parameters[0], "ab");
		fseek(out_bin, pos, SEEK_SET);

		if (loaded)
			save_bin(out_bin, imag);
		if (loaded_rgb)
			for (int i = 0; i < imag.height; i++) {
				for (int j = 0; j < imag.width; j++) {
					unsigned char aux_red =
						(unsigned char)round(imag.matrix_rgb[i][j].red);
					unsigned char aux_green =
						(unsigned char)round(imag.matrix_rgb[i][j].green);
					unsigned char aux_blue =
						(unsigned char)round(imag.matrix_rgb[i][j].blue);

					fwrite(&aux_red, sizeof(unsigned char), 1, out_bin);
					fwrite(&aux_green, sizeof(unsigned char), 1, out_bin);
					fwrite(&aux_blue, sizeof(unsigned char), 1, out_bin);
				}
			}
		fclose(out_bin);
	}

	(*saved) = 1;
}
