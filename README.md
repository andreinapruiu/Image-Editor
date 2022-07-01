&copy; 2021-2022 Andrei Napruiu (napruiuandrei@gmail.com)

# Third PC Homework - Simple Image Editor

> **Mentions before start:**
> + Main code is found inside ***image_editor.c*** file and all the other functions in the rest of .c files.
> + Every function used anywhere in the program can be found(by its header) in only one .h file with its description.
> + The actual pdf with all the requirements for this homework can be found [here](https://github.com/andreinapruiu/pdfs-PC/blob/main/Programare_2021___Tema_3.pdf).
> + The README file included in the repo is just so the checker gives 100 points on this homework.
> + After reading what each command does you can go on and [run the code](#how-to-run-the-code) or [check the problems](#how-to-run-the-checker).

# Contents:
1. [Short Description](#short-description)
2. [Commands](#commands)
3. [Example of running code](#example)
4. [How are the variables used in the program?](#how-are-the-variables-used-in-the-program)
3. [How to run the code?](#how-to-run-the-code)
4. [How to run the checker?](#how-to-run-the-checker)
5. [Other sources](#sources)

# Short description

The program imitates a simple image editor (not like Adobe Photoshop,
but with the same principles) run in CLI with preset functions. By using
this program you can work pixel by pixel with a photo to crop it,
rotate it or even save it in another file if needed.
Special mention: the program works only with some specific types of
images(PPM, PGM)

# Commands
Below is the list of every command (in some cases explained), its input and its output.

> Note: to execute a specific command, besides the input numbers, you need to type the specific word.

## First command - LOAD \<file>
**(loading of an image in memory)**

1. Input:
	- the name of the file to be used later on
2. Process: it takes the file, opens it and then, pixel by pixel
reads it into memory(into a dinamically allocated matrix)
3. Output: 
	- if everything worked just fine, "Loaded \<file>"
	- else it will show a specific message so that the user knows what
didn't work ("Failed to load \<file>" or "Failed to allocate")


## Second command - SELECT \<x1> \<y1> \<x2> \<y2>
**(selecting a portion of an image)**

1. Input:
	- coordinates = self explanatory(the coordinates of a section
of the image, in a xOy coordinates system)
2. Process: it takes the file already loaded and then selects the
exact group of pixels that were sent to input
3. Output:
	- if everything worked just fine,
"Selected \<x1> \<y1> \<x2> \<y2>"
	- else it will show
a specific message so that the user knows what
didn't work ("No image loaded"[if no image was
previously loaded],  "Failed to allocate"
or "Invalid set of coordinates"(if the coordinates given to input
were outside of the file/matrix))


## Third command - SELECT ALL
**(selects the entire image)**

1. Input:
	- just the words "SELECT ALL"
2. Process: it takes the file already loaded and then selects the
entire load of pixels
3. Output:
	- if everything worked just fine, "Selected ALL".
	- else it will show a specific message so that the
user knows what didn't work
("No image loaded"[if no image was previously loaded],
"Failed to allocate")


## Fourth command - ROTATE \<angle>
**(rotates a portion of an image, or the entire image)**

1. Input:
	- angle = self explanatory (the angle based on which the
image will be rotated. Ex: 90, -180 etc)
> Mention: the angle must be a multiple of 90
2. Process: it takes the file already loaded and the selected
pixels from the previous commands and rotates the
selected portion or the image itself
3. Output:
	- if everything worked just fine, "Rotated \<angle>"
	- else it will show a specific message so that the user
knows what didn't work("No image loaded"[if no image was
previously loaded],  "Failed to allocate",
"Unsupported rotation angle"(if the angle given at input isn't
a multiple of 90) or "The selection must be square"(if the
selected area is inside the margins of the image and it's not
a square)


## Fifth command - CROP
**(crops an image)**

1. Input:
	- just the word "CROP
2. Process: the previously selected portion of the image is used
to crop the image
3. Output:
	- if everything worked just fine, "Image cropped".
	- else it will show a specific message so that the user
knows what didn't work("No image loaded"[if no image was
previously loaded] or "Failed to allocate")

## Sixth command - APPLY \<parameter>
**(aplies an effect to the loaded image)**

1. Input:
	- a parameter(EDGE, SHARPEN, BLUR, GAUSSIAN_BLUR)
that is used to determine the newly resulted pixels
2. Process: the loaded file/matrix is separated in smaller pieces
(3x3 pieces to be exact). Then the pieces are united
(by using a formula based on the effect selected) and
after that they form a new pixel. That pixels grouped
with the remaining pieces of the image will form the
new image with the specified effect applied.
3. Output:
	- if everything worked, "APPLY \<parameter> done".
	- else it will show a specific message so that the user
knows what didn't work("No image loaded"[if no image was
previously loaded],  "Failed to allocate",
"APPLY parameter invalid"(if there is no parameter or the one
given at input is not from the list of 4 parameters permitted) or
"Easy,Charlie Chaplin"(if the effect is used on a grayscale image)


## Seventh command - SAVE
**(transpose of a matrix)**

1. Input:
	- filename = self explanatory(the name of the file where
the resulting image should be saved)
	- [**optional**] ascii - if the user wants to save its file
in an ascii format(for PPM and PGM)
2. Process: the matrix coresponding to the image will be printed
out in the file specified(nothing too complicated)
3. Output:
	- if everything worked, "Saved \<filename>".
	- else it will show a specific message so that the user
knows what didn't work("No image loaded"[if no image was
previously loaded] or "Failed to allocate")


## Eighth command - EXIT
**(exiting the program)**

1. Input:
	- just the word "EXIT"
2. Process: the matrix coresponding to the image will be freed
and all the other used structures and variables will
be freed from the memory(for no memory leaks)
3. Output:
	- if everything worked, nothing and the program
is terminated
	- else it will show a specific message so that
the user knows what didn't work
("No image loaded"[if no image waspreviously loaded]
or "Failed to allocate")

## Final Mention
+ All the changes given to an image will not be stored in the
same file, only if the users wants that. The changes will
remain only in the program until the SAVE command is used to
store them in a certain file.

---

# Example

> Supposedly we have a files named color_test_file, grayscale_test_file and color_file in the current folder.

## Input(\>) and Output(<)

\> LOAD color_test_file

< Loaded color_test_file

\> SELECT 0 1 8 10

< Selected 0 1 8 10

\> CROP

< Image cropped

\> SAVE my_binary_file

< Saved my_binary_file

\> LOAD non_existent_file

< Failed to load non_existent_file

\> LOAD color_file

< Loaded color_file

\> APPLY SHARPEN

< APPLY SHARPEN done

\> APPLY BLUR

< APPLY BLUR done

\> APPLY GAUSSIAN_BLUR

< APPLY GAUSSIAN_BLUR done

\> SAVE my_plain_file ascii

< Saved my_plain_file

\> LOAD grayscale_test_file

< Loaded grayscale_test_file

\> APPLY EDGE

< Easy, Charlie Chaplin

\> ROTATE 0

< Rotated 0

\> EXIT


# How are the variables used in the program

**imag** = the struct for the image with all the data needed to work with the file
parameters = all the parameters of any command will be stored here to use later

> Any other variable is self explanatory(loaded to see if an image is loaded in
the program, loaded_rgb to see if an rgb image is loaded in the program,
selected to see if an image has a portion selected etc)

# How to run the code?
1. Download the files as shown in the repo;
2. Open a terminal and change the current directory with the one containing the code;
3. Run the following commands:
	- make
	- ./image_editor
	- the set of commands and numbers/files/strings(data)

## Example
```bash
student@pc:~$ make
gcc -Wall -Wextra -std=c99 -g image_editor.c crop.c load.c rotate.c save.c select.c apply.c -o image_editor -lm
student@pc:~$ ./image_editor 
LOAD input/b.ppm
Loaded input/b.ppm
ROTATE 0
Rotated 0
SAVE test.ppm
Saved test.ppm
EXIT
```

> Note: you can run the code using valgrind to keep track of memory leaks(they don't exist I can assure you)

For valgrind run:
```bash
student@pc:~$ make
gcc -Wall -Wextra -std=c99 -g image_editor.c crop.c load.c rotate.c save.c select.c apply.c -o image_editor -lm
student@pc:~$ valgrind --leak-check=full -s ./image_editor 
LOAD input/b.ppm
Loaded input/b.ppm
ROTATE 0
Rotated 0
SAVE test.ppm
Saved test.ppm
EXIT
```

# How to run the checker?
1. Download the files as shown in the repo;
2. Open a terminal and change the current directory with the one containing the code;
3. Run the following command:

```bash
student@pc:~$ ./check
```

> You will be prompted with a lot of lines verifying a number of inputs for each command. All the inputs can be found in **tasks** folder.

> Note: if the command above doesn't work, you first need to use the following command that will install any other tool needed:
```bash
student@pc:~$ ./install.sh
```

If you want to verify the coding style(based on **Google's coding style**, run:
```bash
student@pc:~$ cs/cs.sh <file>
```

> It will check the coding style on the \<file\> in the tree and print a message inside the command line if it found something irregular.

# Sources:

https://ocw.cs.pub.ro/courses/programare/laboratoare/lab12

https://www.educative.io/edpresso/how-to-convert-a-string-to-an-integer-in-c

https://en.wikipedia.org/wiki/Clamping_(graphics)

https://setosa.io/ev/image-kernels/

https://www.geeksforgeeks.org/rotate-a-matrix-by-90-degree-in-clockwise-direction-without-using-any-extra-space/

http://netpbm.sourceforge.net/doc/pgm.html

http://netpbm.sourceforge.net/doc/ppm.html

---

***Thank you***