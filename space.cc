#include "space.h"


solar_system::solar_system(){

    planets = new celestial_body[5];

}

void solar_system::draw_children(){

    planets[0].draw();
    planets[1].draw();
    planets[2].draw();
    planets[3].draw();
    planets[4].draw();

}

celestial_body::celestial_body(){

}

void celestial_body::draw(){

}

ship::ship(){
    
}