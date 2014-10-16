#include <iostream>
#include "objects.h" //class definition for objects 
using std::cout;




int numpoints = 0;

vec3 points[numpoints];


void myinit(){ //get points

    //output functions for the objects ---> points[]

}

void init(){ //set up buffers, shaders

    GLuint vao; //vertex array object
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    GLuint buffer; //main buffer;
    glGenBuffers(1, &buffer);
    glBindBuffer(GL_ARRAY_BUFFER, buffer);
    //glBufferData()
   
    glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(points), points);
}

extern "C" void display(){

    glClear(GL_COLOR_BUFFER_BIT);  
    //glDrawArrays(GL_TRIANGLES, 0, numpoints);
    glFlush();

}

int main(void){


    return 0;

}


