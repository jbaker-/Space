# This sample Makefile allows you to make an OpenGL application
#   whose source is exactly one .c file under linux.
#   check the location of the X libraries on your implementation.
#
# To use this Makefile, you type:
#
#        make xxxx
#                  
# where
#       xxxx.c is the name of the file you wish to compile 
#       
# A binary named xxxx will be produced
# Libraries are assumed to be in the default search paths
# as are any required include files

#
# Modified by Prof. Chelberg to also allow you to make from a single
# c++ source file.  So if xxxx.cc is the sourcefile, you type make
# xxxx to produce the binary file.

# last-modified: Mon Sep 29 08:50:08 2008 (clarification of comments).

CC = g++

# Assumes the following file exists in the proper place.
include ./Makefile.defs

FILE_NAME = main.cc
EXECUTABLE_NAME = SpaceProject

# patterns to allow compilation of many c++ or c programs
#.c:
#	$(CC)  $@.c   $(InitShader) $(OPTIONS) $(LDLIBS) -o $@

make:
	$(CC)  -c -o space.o space.cc
	$(CC)  -c -o main.o main.cc
	$(CC)  $(OPTIONS) $(LDLIBS) -o $(EXECUTABLE_NAME) main.o space.o $(InitShader) 

clean: 
	rm -f triangle triangle1 polygon0 polygon1
