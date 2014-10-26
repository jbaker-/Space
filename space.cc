#include <space.h>

//default shape for a celestial_body
vec4 cube_coords[36] = {(-1.0, 1.0, 1.0, 1.0f), ( 1.0, 1.0, 1.0, 1.0f), (-1.0,-1.0, 1.0, 1.0f), //first triangle
                        ( 1.0, 1.0, 1.0, 1.0f), ( 1.0,-1.0, 1.0, 1.0f), (-1.0,-1.0, 1.0, 1.0f),
                        ( 1.0, 1.0, 1.0, 1.0f), ( 1.0, 1.0,-1.0, 1.0f), ( 1.0,-1.0, 1.0, 1.0f), 
                        ( 1.0, 1.0,-1.0, 1.0f), ( 1.0,-1.0, 1.0, 1.0f), ( 1.0,-1.0,-1.0, 1.0f),
                        ( 1.0, 1.0,-1.0, 1.0f), ( 1.0,-1.0,-1.0, 1.0f), (-1.0,-1.0,-1.0, 1.0f), // .
                        ( 1.0, 1.0,-1.0, 1.0f), (-1.0, 1.0,-1.0, 1.0f), (-1.0,-1.0,-1.0, 1.0f), // .
                        (-1.0, 1.0,-1.0, 1.0f), (-1.0, 1.0, 1.0, 1.0f), (-1.0,-1.0,-1.0, 1.0f), // .
                        (-1.0, 1.0, 1.0, 1.0f), (-1.0,-1.0,-1.0, 1.0f), (-1.0,-1.0, 1.0, 1.0f),
                        ( 1.0, 1.0, 1.0, 1.0f), (-1.0, 1.0,-1.0, 1.0f), (-1.0, 1.0, 1.0, 1.0f),
                        ( 1.0, 1.0, 1.0, 1.0f), ( 1.0, 1.0,-1.0, 1.0f), (-1.0, 1.0,-1.0, 1.0f),
                        ( 1.0,-1.0, 1.0, 1.0f), ( 1.0,-1.0,-1.0, 1.0f), (-1.0,-1.0,-1.0, 1.0f),
                        ( 1.0,-1.0, 1.0, 1.0f), (-1.0,-1.0,-1.0, 1.0f), (-1.0,-1.0, 1.0, 1.0f)}; //last triangle

/**************************************************************************** 
	The class for the solar system - this holds all the planets, and any 
	moons or stars present
****************************************************************************/

solar_system(GLuint tloc, int num, vec4 *points, vec4 *colors){

	transformloc = tloc; 

	numplanets = num;

	sun = new celestial_body(points, colors, 0, NULL, 0, .1);

	planets[0] = new celestial_body(points, colors, 36, sun, .2, .05);
	planets[1] = new celestial_body(points, colors, 72, sun, .4, .03); //each uses the 36 points of the default cube
	planets[2] = new celestial_body(points, colors, 108, sun, .6, .1);

	moon = new celestial_body(points, colors, 144, planets[0], .1, .02);
}

void solar_system::advance(){



}

void solar_system::draw(){

	sun.draw();

	planets[0].draw();
	planets[1].draw();
	planets[2].draw();

	moon.draw();

}

/****************************************************************************
	The class for an individual celestial body (planet/moon/star)
****************************************************************************/

celestial_body::celestial_body(vec3 *points, vec3 *colors, int index, celestial_body *p, float orb_rad, float object_radius){

	parent = p;											//set parent

	srand(object_radius);

	rotate = vec3(0,0,0);	
	translate = vec3(orb_rad, 0, 0);					//set values used by the transform
	scale.x = scale.y = scale.z = object_radius;

	radius = orb_rad;									//set the radius

	vec4 color = (1/rand(), 1/rand(), 1/rand(), 1.0);	//generate a random color 

	begindex = index;									//set indecies for draw()
	endex = index + 35;

	for(int i = 0; i < 36; i++){
		points[index + i] = cube_coords[i];				//put the points for the object into the points array
		colors[index + i] = color;
	}

}

void celestial_body::draw(){

	update_transform();

	glDrawArrays(GL_TRIANGLES, begindex, endex)

}

void celestial_body::update_transform(){

	transform = Translate(translate) * RotateX(rotate.x) * RotateY(rotate.y) * RotateZ(rotate.z) * Scale(scale) * identity();

}
