#include <Angel.h>

class celestial_body{

public:

	celestial_body(float scale_factor);

	void draw();

private:

	mat4 transform;

	float scale; 	//used to construct the scale portion of the transform
	vec3 translate; //used to construct the translate portion
	vec3 rotate;    //used to construct the rotate portion

	int begindex; //index of first point
	int endex;	  //index of last point - both for making a draw call in the draw() functions

};

class solar_system{

public:

	solar_system();
	~solar_system();

	void draw_children();

	celestial_body *planets;
	celestial_body *star;

private:

};

class ship{

public:

	ship();

	void draw();

private:

	mat4 transform;	//built from position & direction

	vec3 direction; //should keep this normalized
	vec3 position;  //gets updated every update

	float speed;	//determines how far the ship move per update

	int begindex; //first and last points for the ship's points
	int endex;

};

