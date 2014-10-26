#include <space.h>
#include <iostream>
#include <Angel.h>

using std::cout;
using std::endl;

int numpoints;

vec4 *all_points; //pointer to array of all points in the scene
vec4 *all_colors; //pointer to colors array

void init(){

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
   
    // glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(all_points), all_points); 
    //sub-buffers of points and colors
    // glBufferSubData(GL_ARRAY_BUFFER, sizeof(all_points), 
    //          sizeof(all_points) + sizeof(all_colors), all_colors);


    // GLuint program = InitShader("vert_space.glsl", "frag_space.glsl");
    // glUseProgram(program); //initialize shaders

    // GLuint vPosition = glGetAttribLocation(program, "vPosition"); //vPosition
    // glEnableVertexAttribArray(vPosition);
    // glVertexAttribPointer(vPosition, 4, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0));

    // GLuint vColor = glGetAttribLocation(program, "vColor");       //vColor
    // glEnableVertexAttribArray(vColor);
    // glVertexAttribPointer(vColor, 4, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(sizeof(all_points)));

    // transformloc = glGetUniformLocation(program, "transform");
    // camloc = glGetUniformLocation(program, "camera");

    glEnable(GL_DEPTH_TEST);

}

extern "C" void display(){

    glClear(GL_COLOR_BUFFER_BIT);  

    //draw calls

    glFlush();

}

extern "C" void keyboard(unsigned char key, int x, int y){

    mat4 trans; //holds the needed transform;

    switch(key){

        case 033:
            exit(EXIT_SUCCESS); //escape key to exit
            break;

        case 'w':
        case 'W':
            //press to go up
            break;

        case 's':
        case 'S':
            //press to go down
            break;

        case 'a':
        case 'A':
            //press to turn right
            break;

        case 'd':
        case 'D':
            //press to turn left
            break;

    }

    glutPostRedisplay();

}

extern "C" void timerFunc(int value){

    glutTimerFunc(12, timerFunc, 0);
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
    glutTimerFunc(12, timerFunc, 0);

    glutMainLoop();

    return(EXIT_SUCCESS);

}

