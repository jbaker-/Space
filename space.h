#ifndef _SPACE_H_
#define _SPACE_H_

#include "AngelCode/Angel.h"
#include <vector>


//===============================================================================
//The general class for a celestial body - includes sun, planets, moons
//
//By default, the points array is populated by a list of points to make a cube,
//which is just made of triangles - theres currently no way to change it
//===============================================================================


class celestial_body{

public:

	celestial_body(float scale_factor = 1.0);

	void draw();

	int get_numpoints();


	int begindex; //index of first point
	int endex;	  //index of last point - both for making a draw call in the draw() functions

	std::vector<vec3> *points;
	std::vector<vec3> *colors;

private:

	mat4 transform;

	float scale; 	//used to construct the scale portion of the transform
	vec3 translate; //used to construct the translate portion
	vec3 rotate;    //used to construct the rotate portion

	int numpoints = 36;

};

//===============================================================================
//Class for the solar system - has a pointer to the planets, a pointer to the 
//star and a pointer to the moon that circles planet 1
//===============================================================================

class solar_system{

public:

	solar_system();

	void draw_children();
	void advance_one_tick(); //move planets - thisll be fun (oh god no)

    
	celestial_body *star;
	celestial_body *planets;
	celestial_body *moon;

	int numpoints;

private:

};

//===============================================================================
//The ship class, which is the point from which the camera projects - this needs
//a considerable amount of work before any display stuff can occur
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

	// int numpoints;

	// int begindex; //first and last points for the ship's points
	// int endex;

};

#endif
