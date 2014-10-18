#include <iostream>: 
#include "objects.h" //class definition for objects 
using std::cout;



vec3 *all_points; //pointer to array of all points in the scene
vec3 *all_colors; //pointer to colors array

vec3 *all_scales; //pointer to all scale factors
vec3 *all_orients; //pointer to all orient factors
vec3 *all_locations; //pointer to all locate factors


void myinit(){ //get points

    //output functions for the objects ---> points[]

    Object object1;

    object1.gensphere(r, 10, 10);

    object1.color_points(grey, true, 0.05);

}

void init(){ //set up buffers, shaders
t 
    GLuint vao; //vertex array object
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    GLuint buffer; //main buffer;
    glGenBuffers(1, &buffer);
    glBindBuffer(GL_ARRAY_BUFFER, buffer);
    //glBufferData()
   
    glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(all_points), all_points);
}

extern "C" void display(){

    glClear(GL_COLOR_BUFFER_BIT);  
    //glDrawArrays(GL_TRIANGLES, 0, numpoints);
    glFlush();

}

int main(void){


    return 0;

}


