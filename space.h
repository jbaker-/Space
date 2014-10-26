#include <iostream>
#include <cstdlib>
#include <Angel.h>

class solar_system{

	public:

		solar_system(GLuint tloc, int num, vec4 *points, vec4 *colors);

		void advance();

		void draw();

	private:

		GLuint transformloc;

		int numplanets;

		celestial_body* star;
		celestial_body* planets[3];
		celestial_body* moon;

};

class celestial_body{

	public:

		celestial_body(vec4 *points, vec4 *colors, int index, celestial_body *p = NULL, float orb_rad, float object_radius); 
		//puts the points for the celestial body into the array pointed to by *points, colors into *colors
		//starting at the index indicated by the index argument - if there is no parent for the body, then
		//the *p argument is NULL

		void draw();
		//makes and then pushes the mat4 transform as a uniform and then draws the points from "begindex" to "endex" 

		mat4 get_transform(){return transform;}
		vec3 get_position(){return translate;} //to get the parent's position for child's animation

	private:

		mat4 transform;

		void update_transform();

		celestial_body *parent;

		float radius;

		float rot_theta; //rotational angle and its increment
		float rot_theta_increment;

		float orb_theta; //orbital angle and its increment
		float orb_theta_increment;

		int begindex;
		int endex;

		vec3 translate;
		vec3 rotate;
		vec3 scale;

};