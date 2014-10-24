#ifndef _SPACE_CC_
#define _SPACE_CC_

#include "space.h"
#include <cstdlib>

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

    planets[0].draw(transformlocation); //planet 1
    planets[1].draw(transformlocation); //planet 2
    planets[2].draw(transformlocation); //planet 3
    planets[3].draw(transformlocation); //planet 4

    star->draw(transformlocation);      //the star

    moon->draw(transformlocation);   //moon around planet 1

}

void solar_system::advance_one_tick(){ //animates the movement of the planets - used in the timer function
    
    planets[0].increment_theta();
    planets[0].set_translate(vec3(3 * cos(planets[0].get_orbit_theta()), 0, 3 * sin(planets[0].get_orbit_theta()))); //kind of uses arbitrary radii
    planets[0].set_rotate(vec3(0.0f, planets[0].get_rot_theta(), 0.0f));

    planets[1].increment_theta();
    planets[1].set_translate(vec3(5 * cos(planets[1].get_orbit_theta()), 0, 6 * sin(planets[1].get_orbit_theta())));
    planets[1].set_rotate(vec3(0.0f, planets[1].get_rot_theta(), 0.0f));

    planets[2].increment_theta();
    planets[2].set_translate(vec3(9 * cos(planets[2].get_orbit_theta()), 0.0, 8 * sin(planets[2].get_orbit_theta())));
    planets[2].set_rotate(vec3(0.0f, planets[2].get_rot_theta(), 0.0f));

    planets[3].increment_theta();
    planets[3].set_translate(vec3(12 * cos(planets[3].get_orbit_theta()), 0.0, 13 * sin(planets[3].get_orbit_theta())));
    planets[3].set_rotate(vec3(0.0f, planets[3].get_rot_theta(), 0.0f));
    
    star->increment_theta();
    star->set_translate(vec3(0.0, 0.0, 0.0)); 
    star->set_rotate(vec3(0.0f, star->get_rot_theta(), 0.0f));
    
    moon->increment_theta();
    moon->set_translate(vec3(planets[1].get_translate().x + .5 * cos(moon->get_orbit_theta()), 0, planets[1].get_translate().z + .4 * sin(moon->get_orbit_theta())));
    moon->set_rotate(vec3(0.0f, moon->get_rot_theta(), 0.0f));

}

celestial_body::celestial_body(float scale_factor){

    srand(scale_factor);

    begindex = 0;
    endex = 0;

    orbit_theta = 0.0;
    orbit_theta_increment = .05 * (rand() % 40);

    rot_theta = 0.0;
    rot_theta_increment = .01 * (rand() % 200);

    numpoints = 36;

    points = new vec4[36];
    colors = new vec4[36]; 

    vec3 rand_color = vec4(rand(), rand(), rand(), 1.0f);

    for (int i = 0; i < 36; i++){

        points[i] = cube_coords[i];
        colors[i] = rand_color;

    }

    numpoints = 36;

    scale = scale_factor;

    mat4 rx = RotateX(rotate.x);
    mat4 ry = RotateY(rotate.y);
    mat4 rz = RotateZ(rotate.z);

    mat4 t = Translate(translate);
    mat4 s = Scale(scale);

    transform = t * rx * ry * rz * s;
}

void celestial_body::increment_theta(){

    orbit_theta += orbit_theta_increment; 
    rot_theta += rot_theta_increment;

}

vec4 celestial_body::get_point_at(int index){

    vec4 vec;

    vec = points[index];

    return vec;

}

vec4 celestial_body::get_color_at(int index){

    vec4 vec;

    vec = colors[index];

    return vec;

}

void celestial_body::draw(GLint loc){

    //calculate transform and send it as uniform mat4, then draw

    mat4 scale_mat = Scale(scale, scale, scale); //set size
    mat4 orient = RotateY(rotate.y);             //set orientation
    mat4 locate = Translate(translate);          //set position

    transform = locate * orient * scale_mat;     //gather into one mat4

    glUniformMatrix4fv(loc, 1, GL_FALSE, transform); //send to GPU

    glDrawArrays(GL_TRIANGLES, begindex, endex);     //draw

}

int celestial_body::get_numpoints(){
    return numpoints;
}

ship::ship(){

    position = vec4(15, 15, 15, 0);
    direction = vec4(0, 0, 0, 0);
    up = vec4(0, 1, 0, 0);

    speed = 0.1;

}

void ship::advance_one_tick(){

    position += normalize(direction) * speed;

}

void ship::turn(float amount){

    direction = RotateY(amount) * vec4(direction.x, direction.y, direction.z, 1.0);

}
void ship::ascend(float amount){

    position = Translate(0, amount, 0) * vec4(position.x, position.y, position.z, 1.0);

}

#endif
