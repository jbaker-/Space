#makefile for space project - cs4250
#Jonathan Baker jb239812@ohio.edu

INCLUDES = -I./ 
FLAGS = -Wall -lm

make:
	g++ -o space.o $(INCLUDES) $(FLAGS) -c space.cc
	g++ -o main.o  $(INCLUDES) $(FLAGS) -c main.cc
	g++ -o space   $(INCLUDES) $(FLAGS) main.o space.o

clean:
	rm *.o