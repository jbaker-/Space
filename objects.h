#include <iostream>
#include <vector>
#include <Angel.h>
using std::vector;

enum shiptype{s, m, l};
enum color{red, orange, yellow, green, blue, purple, brown, black, white, grey};

vector<vec3> spherepoints[] = {};
vector<vec3> ship_spoints[] = {};
vector<vec3> ship_mpoints[] = {};
vector<vec3> ship_lpoints[] = {};


class object{

    public:

   // misc - wip

	int radius; //for collision - bounding spheres
 	int mass;   //for gravity? dont know if thats going to happen or more specifically, how
	string id;  //if it matters, probably not going to be handling it a lot so it most likely won't 

   // S/O/L for scaling, orienting, and locating the object in the scene

	vec3 scale;
	vec3 orient; 
	vec3 locate;


   // data destined for GPU buffers

	int numpoints; //number of points in the model

	vector<vec3> points; //holds the points
	vector<vec3> colors; //holds the points' colors

   // generating points

	void gensphere(color c); //makes this object a sphere, for planets, moons, main star, etc of color c and radius 1

	void genasteroid(color c); //makes this an object with a surface like what was discussed in class (perturb surface 
					//points by small, random amount times the radius), roughly a sphere of radius 1 and color c

	void genship(shiptype s, color c); //makes this object a ship of type s and color c
	
};

void object::gensphere(color c){

}

void object::genasteroid(color c){

}

void object::genship(shiptype t, color c){
    switch(t){
	case s: points = ship_spoints; break;
	case m: points = ship_mpoints; break;
	case l: points = ship_lpoints; break;
    }
    
    switch(c){
	case red:    for(int i = 0; i < points.size(); i++) colors = vec3(1.0,0.0,0.0); break;
	case orange: for(int i = 0; i < points.size(); i++) colors = vec3(1.0,0.5,0.0); break;
	case yellow: for(int i = 0; i < points.size(); i++) colors = vec3(1.0,1.0,0.0); break;
	case green:  for(int i = 0; i < points.size(); i++) colors = vec3(0.0,1.0,0.0); break;
	case blue:   for(int i = 0; i < points.size(); i++) colors = vec3(0.0,0.0,1.0); break;
	case purple: for(int i = 0; i < points.size(); i++) colors = vec3(0.5,0.0,0.5); break;
	case brown: 
	case black:  for(int i = 0; i < points.size(); i++) colors = vec3(0.0,0.0,0.0); break;
	case white:  for(int i = 0; i < points.size(); i++) colors = vec3(1.0,1.0,1.0); break;
	case grey:   for(int i = 0; i < points.size(); i++) colors = vec3(0.5,0.5,0.5); break;
    }
}

