class celestial_body{

public:

	celestial_body();

	void draw();

private:

	mat4 transform;

	int begindex; //index of first point
	int endex;	  //index of last point - both for making a draw call in the draw() functions

};

class solar_system{

public:

	solar_system();

	void draw_children();

	celestial_body *planets;

private:

};

class ship{

public:

	ship();

	void draw();

private:

	mat4 transform;	//built from 

	vec3 direction; //should keep this normalized
	vec3 position;  //gets updated every update

	float speed;	//determines how far the ship move per update

	int begindex; //first and last points for the ship's points
	int endex;

};

