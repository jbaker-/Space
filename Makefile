#derived from the given makefile by Professor Chelberg

CC = /usr/bin/CC

CC_OPTIONS = +w
INCS = -I/usr/local/include/ -I/home/cs425/code-egs/  -I/home/cs425/code-egs/angel06/include/ -I/opt/csw/include/

OPTIONS = $(CC_OPTIONS)  $(INCS) 

LDLIBS = -L/opt/csw/lib -R/opt/csw/lib -lGLEW -lGL -lglut -lm -lGLU

InitShader = /home/cs425/code-egs/angel06/Common/InitShader.o

Space: main.o space.o
	$(CC) main.o space.o $(InitShader) $(LDLIBS) -o Space

main.o: main.cc
	$(CC) -c main.cc

space.o: space.h space.cc
	$(CC) -c space.cc

clean: 
	rm *.o