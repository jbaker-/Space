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

    GLuint total_size = sizeof(all_points) + sizeof(all_colors);

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

extern "C" void timerFunc(int value){
    
}

extern "C" void keyboard(unsigned char key, int x, int y){

    switch(key){

        case 033:
            exit(EXIT_SUCCESS); //escape key to exit
            break;

        case "W":
        case "w": //up
        break;

        case "S":
        case "s": //down
        break;

        case "A":
        case "a": //left
        break;

        case "D":
        case "d": //right
        break;

        case "E":
        case "e": //roll clockwise
        break;

        case "Q":
        case "q": //roll counter-clockwise
        break;

        case "+": //apply positive thrust
        break;

        case "-": //apply negative thrust
        break;

    }

    glutPostRedisplay();

}

int main(void){


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


