#include "objects.h"

void object::gensphere(char type, int theta_subdivisions, int phi_subdivisions){

	//theta ranges across the entire sphere, from 0 - 2*pi (longitude - East/West)
	//phi ranges from -pi/2 to pi/2 (lattitude - North/South)

	int index = 0;

	float theta = 0;
	float theta_increment = (2*M_PI) / theta_subdivisions;

	float phi = -1 * (M_PI / 2);
	float phi_increment = M_PI / phi_subdivisions;

	switch (type){

		case "r":   //regular sphere

			for (int i = 0; i < phi_subdivisions; i++){

				for (int j = 0; j < theta_subdivisions; j++){

					points[index] = vec3(cos(theta), sin(phi), sin(theta));
					index++;

					theta += theta_increment;
				}

				phi+=phi_increment;

			}

			id = regular_sphere;

			break;

		case "s":	//spiral sphere, kind of a helix

			phi_increment = phi_increment / theta_subdivisions; //made smaller so that durring one revolution
				//itll be incrementally moving towards making a step of the range that would have been the original
				//phi increment

			for (int i = 0; i < phi_subdivisions; i++){

				for (int j = 0; j < theta_subdivisions; j++){

					points[i] = vec3(cos(theta), sin(phi), sin(theta));
					index++;

					theta += theta_increment;
					phi+=phi_increment; //moved into the loop so as to make it easer to render as a strip
						//that is, the strip goes around the sphere like a helix that connects to itself
				}
				
			}

			id = spiral_sphere;

			break;

		default:

			std::cout << "Please use a valid identifier" << endl;

	}
}

void perturb_surface(float roughness){

	srand(sizeof(points));

	for(int i = 0; i < points.size(); i++)
		points[i] += rand() * roughness * points[i]; 
}

void object::genship(char type){
    switch(t){
		case "s": points = ship_spoints; break;
		case "m": points = ship_mpoints; break;
		case "l": points = ship_lpoints; break;
		default:
			std::cout << "Please use a valid identifier" << endl;
    }

    id = ship;
//this needs work, its going to just place points that I have yet to draw out on graph paper
}

void object::color_points(color c){

	vec3 current_color;
    
    switch(c){
		case red:    current_color = vec3(1.0,0.0,0.0); break;
		case orange: current_color = vec3(1.0,0.5,0.0); break;
		case yellow: current_color = vec3(1.0,1.0,0.0); break;
		case green:  current_color = vec3(0.0,1.0,0.0); break;
		case blue:   current_color = vec3(0.0,0.0,1.0); break;
		case purple: current_color = vec3(0.5,0.0,0.5); break;
		case brown:  current_color = vec3(0.9,0.7,0.2); break;
		case black:  current_color = vec3(0.0,0.0,0.0); break;
		case white:  current_color = vec3(1.0,1.0,1.0); break;
		case grey:   current_color = vec3(0.5,0.5,0.5); break;
		default:
			std::cout << "Please use a valid identifier" << endl;
    }

    for(int i = 0; i < points.size(); i++)
    	colors[i] = current_color;
//takes the color value and colors all points within the object and gives them all a solid color with that value
}

void object::place_in_world(vec3 scale_factor, vec3 orientation, vec3 location){
	scale = scale_factor;
	orient = orientation;
	locate = location;
}