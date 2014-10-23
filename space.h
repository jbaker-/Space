#include <Angel.h>
#include <vector>

vec3 cube_points[36] = {(-.5, .5, .5), ( .5, .5, .5), (-.5,-.5, .5), //first triangle
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

//===============================================================================
//The general class for a celestial body - includes sun, planets, moons
//===============================================================================


class celestial_body{

public:

	celestial_body(float scale_factor);

	void draw();

private:

	std::vector<vec3> points;
	std::vector<vec3> colors;

	mat4 transform;

	float scale; 	//used to construct the scale portion of the transform
	vec3 translate; //used to construct the translate portion
	vec3 rotate;    //used to construct the rotate portion

	int begindex; //index of first point
	int endex;	  //index of last point - both for making a draw call in the draw() functions

};

//===============================================================================
//Class for the solar system - has a pointer to the planets and a pointer to 
//===============================================================================

class solar_system{

public:

	solar_system();
	~solar_system();

	void draw_children();

    
	celestial_body *star;
	celestial_body *planets;
	celestial_body *moons;

private:
	int numpoints;
};

//===============================================================================
//The ship class, which is the point from which the camera projects
//===============================================================================


class ship{

public:

	ship();

	void draw();

private:

	mat4 transform;	//built from position & direction

	vec3 direction; //should keep this normalized
	vec3 position;  //gets updated every update

	float speed;	//determines how far the ship move per update

	int numpoints;

	int begindex; //first and last points for the ship's points
	int endex;

};

