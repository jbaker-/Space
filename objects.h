#include <iostream>
#include <vector>
#include <Angel.h>
#include <cstdlib>
using std::vector;

enum color{red, orange, yellow, green, blue, purple, brown, black, white, grey};

enum type{currently_undefined, error, spiral_sphere, regular_sphere, ship};

vector<vec3> ship_spoints[] = {};
vector<vec3> ship_mpoints[] = {}; //these are going to need to be implemented yet
vector<vec3> ship_lpoints[] = {};

vector<vec3> error[] = {(-0.5, 0.5, 0.0), ( 0.5,  0.5, 0.0), (-0.5, -0.5, 0.0), //to have a visual representation of a
						( 0.5, 0.5, 0.0), (-0.5, -0.5, 0.0), ( 0.5, -0.5, 0.0)} 

class Object{

    public:
    Object();

   //=============================
   // generating & coloring points
   //=============================
	void genship(char type); //copies the points for the selected type of ship

	int gensphere(char type, int theta_subdivisions, int phi_subdivisions); //makes this object a unit sphere
	//types include "r" and "s" currently, where r is regular and s is spiral;


	void perturb_surface(float roughness); //used for roughening the surface of the sphere, but theres no reason 
		// you couldnt do it to a ship - should totally do that once I get a bit further 
	    // values for roughness determine maximum for a random offset from the origin
		//
		// 	e.g. v += roughness value * v  so probably limit it to .05 or thereabouts
		//
		// note: probably not best to use this on a "regular sphere", itll offset the triangles' verticies 
		//			individually rather than in a coherent fashion

	void color_points(color c, bool rand, float weight); //if rand is true, the colors will be given 
		//a random offset per vertex based upon the value of weight

   //===========
   // misc - wip
   //===========
    	
	// int radius; //for collision - bounding spheres
 	// int mass;   //for gravity? dont know if thats going to happen or more specifically, how
	

	void place_in_world(vec3 scale_factor, vec3 orientation, vec3 location);   //pass through to set
		//S/O/L for scaling, orienting, and locating the object in the scene - for transforming the object

   //=============================
   //data destined for GPU buffers
   //=============================

	int numpoints; //number of points in the model

	vector<vec3> *points; //holds the points
	vector<vec3> *colors; //holds the points' colors

	void output(); //some of the code from gensphere() might need to move here

    private:

    type id; //holds what kind of object this is

	vec3 scale;
	vec3 orient; 
	vec3 locate;


};