space: object.o
	g++ -o space space.o objects.o

space.o: space.cc
	g++ -c space.cc

objects.o: objects.h objects.cc
	g++ -c objects.cc

clean: 
	rm *.o