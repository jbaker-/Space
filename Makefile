#derived from the given makefile by Professor Chelberg

CC = /usr/bin/g++

CC_OPTIONS = +w
#INCS = -I/usr/local/include/ -I/home/cs425/code-egs/  -I/home/cs425/code-egs/angel06/include/ -I/opt/csw/include/
INCS = -I./AngelCode/

OPTIONS = $(CC_OPTIONS)  $(INCS) 

LDLIBS = -lGLEW -lGL -lglut -lm -lGLU -g
#-L/opt/csw/lib -R/opt/csw/lib 


Space: 
	$(CC) -c main.cc
	$(CC) -c space.cc
	$(CC) main.o space.o $(LDLIBS) -o SpaceProject

clean: 
	rm *.o