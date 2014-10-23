#include <iostream>
#include "space.h" //class definition for objects 
#include "AngelCode/Angel.h"
using std::cout;

int numpoints;

vec3 *all_points; //pointer to array of all points in the scene
vec3 *all_colors; //pointer to colors array

solar_system ss; //the solar system, holds all the planets and other celestial bodies

void myinit(){ //get points

    //output functions for the objects ---> points[]

    //once all points are present, give each object a starting index and an ending index to use in the draw() function
    //also make sure each knows whether to use GL_TRIANGLES or GL_TRIANGLE_STRIP, etc 
    //e.g. draw() leads to a call of glDrawArrays(primitivetype, start, end)

    numpoints = ss.numpoints;

    all_points = new vec3[numpoints];
    all_colors = new vec3[numpoints];

    int index = 0;

    ss.star->set_begindex(index);

    for (int i = 0; i < 36; i++){
        all_points[index] = ss.star->get_point_at(index);
        index++;
    }

    ss.star->set_endex(index);

    for (int j = 0; j < 4; j++){

        ss.planets[j].set_begindex(index);

        for (int k = 0; k < 36; k++){
            all_points[index] = ss.planets[j].get_point_at(k);
            index++;
        }

        ss.planets[j].set_endex(index - 1);
    }

    ss.moon->set_begindex(index);

    for (int l = 0; l < 36; l++){
        all_points[index] = ss.moon->get_point_at(l);
        index++;
    }

    ss.moon->set_endex(numpoints - 1);

}

void init(){ //set up buffers, shaders

    GLuint total_size = sizeof(all_points) + sizeof(all_colors);

    GLuint vao; //vertex array object
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    GLuint buffer; //main buffer;
    glGenBuffers(1, &buffer);
    glBindBuffer(GL_ARRAY_BUFFER, buffer);
    //glBufferData()
   
    glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(all_points), all_points);
    glBufferSubData(GL_ARRAY_BUFFER, sizeof(all_points), sizeof(all_points) + sizeof(all_colors), all_colors);
}

extern "C" void display(){

    glClear(GL_COLOR_BUFFER_BIT);  
    //glDrawArrays(GL_TRIANGLES, 0, numpoints);

    ss.draw_children();

    glFlush();

    //get this down to one call main.draw()
    //which calls draw() on each of its children

}

extern "C" void timerFunc(int value){
    
}

extern "C" void keyboard(unsigned char key, int x, int y){

    switch(key){

        case 033:
            exit(EXIT_SUCCESS); //escape key to exit
            break;

        case 'W':
        case 'w': //up
        break;

        case 'S':
        case 's': //down
        break;

        case 'A':
        case 'a': //left
        break;

        case 'D':
        case 'd': //right
        break;

        // case 'E':
        // case 'e': //roll clockwise
        // break;

        // case 'Q':
        // case 'q': //roll counter-clockwise
        // break;

        case '+': //apply positive thrust
        break;

        case '-': //apply negative thrust
        break;

    }

    glutPostRedisplay();

}

int main(int argc, char **argv){


    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGBA | GLUT_DEPTH);

    glutInitWindowSize(640, 480);
    glutCreateWindow("Space, the final frontier");

    glewInit();

    myinit(); //get all the points generated
    init();   //get all the buffers allocated, and points and associated data loaded in

    glutDisplayFunc(display);
    glutKeyboardFunc(keyboard);

    glutMainLoop();

    return(EXIT_SUCCESS);

}


