Copyright Andrei Napruiu 312CA 2022
-------------------------------Short description-------------------------------

	 The program imitates a simple image editor (not like Adobe Photoshop,
	but with the same principles) run in CLI with preset function. By using
	   this program you can work pixel by pixel with a photo to crop it,
		rotate it or even save it in another file if needed.
	Special mention: the program works only with some specific types of
				  images(PPM, PGM)

-----------------------------------Commands------------------------------------


			 ## First command - LOAD <file>##
			 (loading of an image in memory)

	     1. Input: - the name of the file to be used later on
	     2. Process: it takes the file, opens it and then, pixel by pixel
	     	     reads it into memory(into a dinamically allocated matrix)
	     3. Output: if everything worked just fine, "Loaded <file>". Else
	     it will
	     		show a specific message so that the user knows what
	     	  didn't work ("Failed to load <file>" or "Failed to allocate")


		## Second command - SELECT <x1> <y1> <x2> <y2> ##
			  (selecting a portion of an image)

	     1. Input: coords = self explanatory(the coordinates of a section
	     			of the image, in a xOy coordinates system)
	     2. Process: it takes the file already loaded and then selects the
	     			exact group of pixels that were sent to input
	     3. Output: 	if everything worked just fine,
	     		"Selected <x1> <y1> <x2> <y2>". Else it will show
	     		a specific message so that the user knows what
	     	   didn't work ("No image loaded"[if no image was
	     	   	previously loaded],  "Failed to allocate"
	     or "Invalid set of coordinates"(if the coordinates given to input
	     			were outside of the file/matrix))


			  ## Third command - SELECT ALL ##
			     (selects the entire image)

	     1. Input: just the words "SELECT ALL"
	     2. Process: it takes the file already loaded and then selects the
	     			entire load of pixels
	     3. Output: if everything worked just fine, "Selected ALL".
	     		Else it will show a specific message so that the
	     		user knows what didn't work
	     	 ("No image loaded"[if no image was previously loaded],
	     			"Failed to allocate")


			 ## Fourth command - ROTATE <angle> ##
		(rotates a portion of an image, or the entire image)

	     1. Input: angle = self explanatory (the angle based on which the
	     			image will be rotated. Ex: 90, -180 etc)
	     		- Mention: the angle must be a multiple of 90
	     2. Process: it takes the file already loaded and the selected
	     		pixels from the previous commands and rotates the
	     			selected portion or the image itself
	     3. Output: if everything worked just fine, "Rotated <angle>".
	     		Else it will show a specific message so that the user
	     	      knows what didn't work("No image loaded"[if no image was
	     	   	previously loaded],  "Failed to allocate",
	     "Unsupported rotation angle"(if the angle given at input isn't
	     a multiple of 90) or "The selection must be square"(if the
	     selected area is inside the margins of the image and it's not
	     				a square)


			     ## Fifth command - CROP ##
			     (crops an image)

	     1. Input: just the word "CROP
	     2. Process: the previously selected portion of the image is used
	     			to crop the image
	     3. Output: if everything worked just fine, "Image cropped".
	     		Else it will show a specific message so that the user
	     	      knows what didn't work("No image loaded"[if no image was
	     	   	previously loaded] or "Failed to allocate")

			 ## Sixth command - APPLY <parameter> ##
			 (aplies an effect to the loaded image)

	     1. Input: - a parameter(EDGE, SHARPEN, BLUR, GAUSSIAN_BLUR)
	     		that is used to determine the newly resulted pixels
	     2. Process: the loaded file/matrix is separated in smaller pieces
	     		(3x3 pieces to be exact). Then the pieces are united
	     		(by using a formula based on the effect selected) and
	     		after that they form a new pixel. That pixels grouped
	     		with the remaining pieces of the image will form the
	     		   new image with the specified effect applied.
	     3. Output: if everything worked, "APPLY <parameter> done".
	     		Else it will show a specific message so that the user
	     	      knows what didn't work("No image loaded"[if no image was
	     	   	previously loaded],  "Failed to allocate",
	      "APPLY parameter invalid"(if there is no parameter or the one
	      given at input is not from the list of 4 parameters permitted) or
	     "Easy,Charlie Chaplin"(if the effect is used on a grayscale image)


			     ## Seventh command - SAVE ##
			     (transpose of a matrix)

	     1. Input: filename = self explanatory(the name of the file where
	     		the resulting image should be saved)
	     		*optional* ascii - if the user wants to save its file
	     				in an ascii format(for PPM and PGM)
	     2. Process: the matrix coresponding to the image will be printed
	     		   out in the file specified(nothing too complicated)
	     3. Output: if everything worked, "Saved <filename>".
	     		Else it will show a specific message so that the user
	     	      knows what didn't work("No image loaded"[if no image was
	     	   	previously loaded] or "Failed to allocate")


			     ## Eighth command - EXIT ##
			     	(exiting the program)

	     1. Input: just the word "EXIT"
	     2. Process: the matrix coresponding to the image will be freed
	     		 and all the other used structures and variables will
	     		   be freed from the memory(for no memory leaks)
	     3. Output: if everything worked, nothing and the program
	     	is terminated. Else it will show a specific message so that
	     		   the user knows what didn't work
	     	   ("No image loaded"[if no image waspreviously loaded]
	     			or "Failed to allocate")

				## Final Mention ##
	     1. All the changes given to an image will not be stored in the
	     	same file, only if the users wants that. The changes will
	     	remain only in the program until the SAVE command is used to
	     		   store them in a certain file.

------------------How are the variables used in the program--------------------

imag = the struct for the image with all the data needed to work with the file
parameters = all the parameters of any command will be stored here to use later

Any other variable is self explanatory(loaded to see if an image is loaded in
the program, loaded_rgb to see if an rgb image is loaded in the program,
selected to see if an image has a portion selected etc)

------------------------------------Sources:-----------------------------------

https://ocw.cs.pub.ro/courses/programare/laboratoare/lab12
https://www.educative.io/edpresso/how-to-convert-a-string-to-an-integer-in-c
https://en.wikipedia.org/wiki/Clamping_(graphics)
https://setosa.io/ev/image-kernels/
https://www.geeksforgeeks.org/rotate-a-matrix-by-90-degree-in-clockwise-direction-without-using-any-extra-space/
http://netpbm.sourceforge.net/doc/pgm.html
http://netpbm.sourceforge.net/doc/ppm.html

-------------------------------------------------------------------------------
