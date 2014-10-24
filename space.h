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

	celestial_body(float scale_factor = 0.1);

	void draw(GLint loc);

	int get_numpoints();


	vec4 *points;	//holds the points and colors of the planet/moon/star/whatever
	vec4 *colors;

	void set_begindex(int index){begindex = index;} //used when putting the points into the main array
	void set_endex(int index){endex = index;}

	vec4 get_point_at(int index);	//accessor functions, because there was an issue with 
	vec4 get_color_at(int index);	//casting when I tried to access directly for some reason
									//it kept trying to assign a vector<vec3> to a vec3, even though I was dereferencing it

	float get_orbit_theta(){return orbit_theta;}		//for animation of the planets around the star
	float get_rot_theta(){return rot_theta;}

	void increment_theta();	//called every update

	void set_translate(vec3 set){translate = set;}
	vec3 get_translate(){return translate;}

	void set_rotate(vec3 set){rotate = set;}

private:

	mat4 transform;

	float scale; 	//used to construct the scale portion of the transform
	vec3 translate; //used to construct the translate portion
	vec3 rotate;    //used to construct the rotate portion

	int begindex; //index of first point
	int endex;	  //index of last point - both for making a draw call in the draw() functions

	int numpoints;

	float orbit_theta;
	float orbit_theta_increment; //for revolutions about the star

	float rot_theta;
	float rot_theta_increment;	//for rotations about its axis



};

//===============================================================================
//Class for the solar system - has a pointer to the planets, a pointer to the 
//star and a pointer to the moon that circles planet 1
//===============================================================================

class solar_system{

public:

	solar_system();

	void draw_children(); //sends the location to send the matrix to
	void advance_one_tick(); //move planets - aka update_children
	void set_transform_pointer_loc(GLint set){transformlocation = set;}

    
	celestial_body *star;
	celestial_body *planets;
	celestial_body *moon;

	int numpoints;
	GLint transformlocation;

private:

};

//===============================================================================
//The ship class, which is the point from which the camera projects 
//===============================================================================


class ship{

public:

	ship();

	//void draw();

	vec4 get_position(){return position;}
	vec4 get_direction(){return direction;}
	vec4 get_up(){return up;}
	float get_speed(){return speed;}

	void set_position(vec3 pos){position = pos;}
	void set_direction(vec3 dir){direction = dir;}

	void advance_one_tick();

	void speed_up(){speed += .1;} 
	void slow_down(){speed -= .1;} //can go negative - to move backwards

	void turn(float amount);
	void ascend(float amount);

private:

	//mat4 transform;	//built from position & direction

	vec4 direction; 
	vec4 position;  //gets updated every update
	vec4 up;

	float speed;	//determines how far the ship move per update

	// int numpoints;

	// int begindex; //first and last points for the ship's points
	// int endex;

};

#endif
