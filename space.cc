#ifndef _SPACE_CC_
#define _SPACE_CC_

#include "space.h"

//default shape for a celestial_body
vec3 cube_coords[36] = {(-.5, .5, .5), ( .5, .5, .5), (-.5,-.5, .5), //first triangle
                        ( .5, .5, .5), ( .5,-.5, .5), (-.5,-.5, .5),
                        ( .5, .5, .5), ( .5, .5,-.5), ( .5,-.5, .5), 
                        ( .5, .5,-.5), ( .5,-.5, .5), ( .5,-.5,-.5),
                        ( .5, .5,-.5), ( .5,-.5,-.5), (-.5,-.5,-.5), // .
                        ( .5, .5,-.5), (-.5, .5,-.5), (-.5,-.5,-.5), // .
                        (-.5, .5,-.5), (-.5, .5, .5), (-.5,-.5,-.5), // .
                        (-.5, .5, .5), (-.5,-.5,-.5), (-.5,-.5, .5),
                        ( .5, .5, .5), (-.5, .5,-.5), (-.5, .5, .5),
                        ( .5, .5, .5), ( .5, .5,-.5), (-.5, .5,-.5),
                        ( .5,-.5, .5), ( .5,-.5,-.5), (-.5,-.5,-.5),
                        ( .5,-.5, .5), (-.5,-.5,-.5), (-.5,-.5, .5)}; //last triangle

solar_system::solar_system(){


    star = new celestial_body(10);
    planets = new celestial_body[4];
    moon = new celestial_body(1);



    numpoints = star->get_numpoints();
    numpoints += moon->get_numpoints();

    for (int i = 0; i < 4; i++){
        numpoints += planets[i].get_numpoints();
    }

}

void solar_system::draw_children(){

    planets[0].draw(); //planet 1
    planets[1].draw(); //planet 2
    planets[2].draw(); //planet 3
    planets[3].draw(); //planet 4

    star->draw();      //the star

    moon->draw();   //moon around planet 1

}

celestial_body::celestial_body(float scale_factor){

    begindex = 0;
    endex = 0;
    numpoints = 36;

    points = new std::vector<vec3> (&cube_coords[0], &cube_coords[0] + sizeof(cube_coords));
    colors = new std::vector<vec3> (points->size());

    numpoints = points->size();

    scale = scale_factor;

    mat4 rx = RotateX(rotate.x);
    mat4 ry = RotateY(rotate.y);
    mat4 rz = RotateZ(rotate.z);

    mat4 t = Translate(translate);
    mat4 s = Scale(scale);

    transform = t * rx * ry * rz * s;
}

void celestial_body::draw(){

    glDrawArrays(GL_TRIANGLES, begindex, endex);

}

int celestial_body::get_numpoints(){
    return numpoints;
}

ship::ship(){

}

#endif
