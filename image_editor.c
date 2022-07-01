// Copyright 2022 Andrei Napruiu

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "image_editor.h"
#include "load.h"
#include "save.h"
#include "select.h"
#include "crop.h"
#include "rotate.h"
#include "apply.h"

// Function to read the command and then save it in a variable
// so it can be used later on in the program
commands change_command(char *command, char **parameters)
{
	char *p = strchr(command, '\n');
	char **input = malloc(MAXCOM * sizeof(char *));
	char *tok = strtok(command, " ");
	int i = 0;

	if (p)
		*p = '\0';

	while (tok) {
		input[i] = tok;
		tok = strtok(NULL, " ");
		i++;
	}

	if (strcmp(input[0], "LOAD") == 0) {
		if (i != 2) {
			free(input);
			return NO;
		}
		parameters[0] = input[1];

		free(input);
		return LOAD;
	} else if (strcmp(input[0], "SELECT") == 0) {
		if (strcmp(input[1], "ALL") == 0) {
			free(input);
			return SELECT_ALL;
		}

		if (i < 5 || i > 5) {
			free(input);
			return NO;
		}

		i = 0;
		while (i < MAXPAR) {
			if (!isdigit(input[i + 1][0]) && !isdigit(input[i + 1][1])) {
				free(input);
				return NO;
			}
			parameters[i] = input[i + 1];
			i++;
		}

		free(input);
		return SELECT;
	} else if (strcmp(input[0], "ROTATE") == 0) {
		parameters[0] = input[1];

		free(input);
		return ROTATE;
	} else if (strcmp(input[0], "CROP") == 0) {
		free(input);
		return CROP;
	} else if (strcmp(input[0], "APPLY") == 0) {
		if (i == 2)
			parameters[0] = input[1];

		free(input);
		return APPLY;
	} else if (strcmp(input[0], "SAVE") == 0) {
		if (i != 3)
			input[2] = "\0";

		for (i = 0; i < MAXPAR - 2; i++)
			parameters[i] = input[i + 1];

		free(input);
		return SAVE;
	} else if (strcmp(input[0], "EXIT") == 0) {
		free(input);
		return 8; // for some reason, the style checker didn't agree with EXIT
	}

	free(input);
	return NO;
}

// All the functions below have the same purpose - to solve the case
// they represent. They were created just to have a much more
// modularized code
void solve_load(char **parameters, image *imag,
				int *loaded, int *loaded_rgb, int *selected_all)
{
	load_any(parameters, imag, loaded, loaded_rgb);
	if (*loaded == 1 || *loaded_rgb == 1) {
		selecting_all(imag, selected_all);
		printf("Loaded %s\n", parameters[0]);
	} else {
		printf("Failed to load %s\n", parameters[0]);
	}
}

void solve_select(char **parameters, image *imag,
				  int loaded, int loaded_rgb, int *selected)
{
	if (loaded == 1 || loaded_rgb == 1) {
		selecting(parameters, imag, selected);
		if (*selected == 1)
			*selected = 0;
	} else {
		printf("No image loaded\n");
	}
}

void solve_selectall(image *imag, int loaded, int loaded_rgb,
					 int *selected_all)
{
	if (loaded == 1 || loaded_rgb == 1) {
		selecting_all(imag, selected_all);
		if (*selected_all == 1) {
			printf("Selected ALL\n");
			*selected_all = 0;
		}
	} else {
		printf("No image loaded\n");
	}
}

void solve_rotate(char **parameters, image *imag,
				  int loaded, int loaded_rgb, int *rotated)
{
	if (loaded == 1 || loaded_rgb == 1) {
		rotate_any(imag, parameters, loaded, loaded_rgb, rotated);
		if (*rotated == 1) {
			printf("Rotated %s\n", parameters[0]);
			*rotated = 0;
		}
	} else {
		printf("No image loaded\n");
	}
}

void solve_crop(image *imag, int loaded, int loaded_rgb, int *cropped)
{
	if (loaded == 1 || loaded_rgb == 1) {
		crop_any(imag, loaded, loaded_rgb, cropped);
		if (*cropped == 1) {
			printf("Image cropped\n");
			*cropped = 0;
		}
	} else {
		printf("No image loaded\n");
	}
}

void solve_save(char **parameters, image imag,
				int loaded, int loaded_rgb, int *saved)
{
	if (loaded == 1 || loaded_rgb == 1) {
		save_any(parameters, imag, loaded, loaded_rgb, saved);
		if (*saved == 1) {
			printf("Saved %s\n", parameters[0]);
			*saved = 0;
		}
	} else {
		printf("No image loaded\n");
	}
}

void solve_apply(char **parameters, image *imag,
				 int loaded, int loaded_rgb, int *applied)
{
	if (loaded == 1) {
		if (strcmp(parameters[0], "") != 0)
			printf("Easy, Charlie Chaplin\n");
		else
			printf("Invalid command\n");
	} else if (loaded_rgb == 1) {
		apply_any(parameters, imag, applied);
		if (*applied == 1) {
			printf("APPLY %s done\n", parameters[0]);
			*applied = 0;
		} else {
			printf("APPLY parameter invalid\n");
		}
	} else {
		printf("No image loaded\n");
	}
}

int main(void)
{
	int loaded = 0, loaded_rgb = 0, saved = 0, selected = 0, selected_all = 0;
	int cropped = 0, rotated = 0, applied = 0;
	image imag = {0};
	char **parameters = malloc(MAXPAR * sizeof(char *));
	if (!parameters)
		printf("Error with the allocation\n");

	char *command = malloc(COMSIZE * sizeof(char));
	if (!command)
		printf("Error with the allocation\n");

	commands option = NO;

	while (option != EXIT) {
		fgets(command, COMSIZE, stdin);
		option = change_command(command, parameters);

		switch (option) {
		case LOAD:
			solve_load(parameters, &imag, &loaded, &loaded_rgb, &selected_all);
			break;
		case SELECT:
			solve_select(parameters, &imag, loaded, loaded_rgb, &selected);
			break;
		case SELECT_ALL:
			solve_selectall(&imag, loaded, loaded_rgb, &selected_all);
			break;
		case ROTATE:
			solve_rotate(parameters, &imag, loaded, loaded_rgb, &rotated);
			break;
		case CROP:
			solve_crop(&imag, loaded, loaded_rgb, &cropped);
			break;
		case APPLY:
			solve_apply(parameters, &imag, loaded, loaded_rgb, &applied);
			break;
		case SAVE:
			solve_save(parameters, imag, loaded, loaded_rgb, &saved);
			break;
		case EXIT:
			if (loaded == 1)
				free_matrix(imag.matrix, imag.height);
			if (loaded_rgb == 1)
				free_matrix_rgb(imag.matrix_rgb, imag.height);
			if (loaded == 0 && loaded_rgb == 0)
				printf("No image loaded\n");
			break;
		case NO:
			printf("Invalid command\n");
			break;
		default:
			printf("Invalid command\n");
			break;
		}
	}

	free(parameters);
	free(command);
	return 0;
}
