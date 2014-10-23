#include "space.h"


solar_system::solar_system(){

    planets = new celestial_body[6];

    star = new celestial_body();

    numpoints = star.numpoints;

}

solar_system::~solar_system(){

    delete planets;
    delete star;

}

void solar_system::draw_children(){

    planets[0].draw(); //planet 1
    planets[1].draw(); //planet 2
    planets[2].draw(); //planet 3
    planets[3].draw(); //planet 4
    planets[4].draw(); //moon 1 - around planet 1
    planets[5].draw(); //asteroid

}

celestial_body::celestial_body(float scale_factor){

    

    numpoints = points.size;

    scale = scale_factor;

    mat4 r = Rotate(rotate);
    mat4 t = Translate(translate);
    mat4 s = Scale(scale);

    transform = t * r * s;
}

void celestial_body::draw(){

    glDrawArrays(GL_TRIANGLES, begindex, endex);

}

ship::ship(){

}