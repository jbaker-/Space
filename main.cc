#include <iostream>
#include "space.h" //class definition for objects 
#include "AngelCode/Angel.h"
using std::cout;

int numpoints;

vec4 *all_points; //pointer to array of all points in the scene
vec4 *all_colors; //pointer to colors array

solar_system ss; //the solar system, holds all the planets and other celestial bodies
ship ship_1;          //the location of the camera

GLint transformloc; //sent per object, per draw call
GLint camloc;

void myinit(){ //get points

    //output functions for the objects ---> points[]

    //once all points are present, give each object a starting index and an ending index to use in the draw() function
    //also make sure each knows whether to use GL_TRIANGLES or GL_TRIANGLE_STRIP, etc 
    //e.g. draw() leads to a call of glDrawArrays(primitivetype, start, end)

    numpoints = ss.numpoints;

    all_points = new vec4[numpoints];
    all_colors = new vec4[numpoints];

    int index = 0;

    ss.star->set_begindex(index);

    for (int i = 0; i < 36; i++){
        all_points[index] = ss.star->get_point_at(index);
        all_colors[index] = ss.star->get_color_at(index);
        index++;
    }

    ss.star->set_endex(index);

    for (int j = 0; j < 4; j++){

        ss.planets[j].set_begindex(index);

        for (int k = 0; k < 36; k++){
            all_points[index] = ss.planets[j].get_point_at(k);
            all_colors[index] = ss.planets[j].get_color_at(k);
            index++;
        }

        ss.planets[j].set_endex(index - 1);
    }

    ss.moon->set_begindex(index);

    for (int l = 0; l < 36; l++){
        all_points[index] = ss.moon->get_point_at(l);
        all_colors[index] = ss.moon->get_color_at(l);
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
   
    glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(all_points), all_points); //sub-buffers of points and colors
    glBufferSubData(GL_ARRAY_BUFFER, sizeof(all_points), sizeof(all_points) + sizeof(all_colors), all_colors);


    GLuint program = InitShader("vert_space.glsl", "frag_space.glsl");
    glUseProgram(program); //initialize shaders

    GLuint vPosition = glGetAttribLocation(program, "vPosition"); //vPosition
    glEnableVertexAttribArray(vPosition);
    glVertexAttribPointer(vPosition, 4, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0));

    GLuint vColor = glGetAttribLocation(program, "vColor");       //vColor
    glEnableVertexAttribArray(vColor);
    glVertexAttribPointer(vColor, 4, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(sizeof(all_points)));

    transformloc = glGetUniformLocation(program, "transform");
    camloc = glGetUniformLocation(program, "camera");

    glEnable(GL_DEPTH_TEST);


    ss.set_transform_pointer_loc(transformloc);
}

extern "C" void display(){

    glClear(GL_COLOR_BUFFER_BIT);  

    glUniformMatrix4fv(camloc, 1, GL_FALSE, LookAt(ship_1.get_position(), ship_1.get_direction(), ship_1.get_up()));

    ss.draw_children();

    glFlush();

}

extern "C" void timerFunc(int value){

    ss.advance_one_tick(); //move planets forward in time
    ship_1.advance_one_tick();  //move ship forward (backward if s.speed < 0) on its course

    GLuint time_per_frame = 12;

    glutTimerFunc(time_per_frame, timerFunc, 0);
}

extern "C" void keyboard(unsigned char key, int x, int y){

    mat4 trans; //holds the needed transform;

    switch(key){

        case 033:
            exit(EXIT_SUCCESS); //escape key to exit
            break;

        case 'W':
        case 'w': ship_1.ascend(.1);//up
        break;

        case 'S':
        case 's': ship_1.ascend(-.1); //down
                  std::cout<< "distance from 0,0,0 = " << length(ship_1.get_position()) << std::endl
                           << "current position = " << ship_1.get_position() << std::endl
                           << "speed = " << ship_1.get_speed() << std::endl;
        break;

        case 'A':
        case 'a': ship_1.turn(-.1); //left
        break;

        case 'D':
        case 'd': ship_1.turn(.1); //right
        break;

        case '+': ship_1.speed_up(); //apply positive thrust
        break;

        case '-': ship_1.slow_down();//apply negative thrust
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
    glutTimerFunc(12, timerFunc, 0);

    glutMainLoop();

    return(EXIT_SUCCESS);

}


