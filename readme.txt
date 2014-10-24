Jonathan Baker - jb239812@ohio.edu
CS 4250 Space Project Readme

I think for the most part I have everything I can see debugged, everything compiles and runs but I'm not getting any output to the screen despite 
having messed with it a whole heck of a lot.

update 10/24/2014: I tried adding an output of the distance to zero to the downward movement function of the ship, and its outputting -NaN, which doesnt sound good

The code is organized into the shaders, the main.cc file, and space.h and .cc files, which contain:

-shaders (vert_space.glsl and frag_space.glsl):

	-The vertex shader takes the 4x4 matricies from the main function (the one representing the camera and the one representing the transform for the point)
	and multiplies them thusly - Camera * Transform * Point

	-The fragment shader is a simple pass-through

-main.cc:

	-Declaration of all objects used (the solar system, the ship)

    -All initialization of shaders, buffers

    -GLUT functions (keyboard, timer, display)

-space.h and .cc:

	-Definitions of the classes used(solar_system, celestial_body, ship)

	-All the associated functions(accesors, animation, ship control, draw calls)

The solar_system class has pointers to several (specifically 6 -- 4 planets, 1 moon, 1 star) objects of the celestial_object class.
The solar_system class also has a function called draw_children() which is called in the display function (after sending a 4x4 matrix using glUniformMatrix4fv()),
which calls draw() on all of the celestial_object objects that it holds, each of which calculate and send a 4x4 transform matrix to the GPU via glUniformMatrix4fv()
and the make a draw call corresponding to the object whose transform was sent.
