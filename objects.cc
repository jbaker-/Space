#include "objects.h"

Object::Object(){
	id = currently_undefined;

	points = NULL;
	colors = NULL;
}

int Object::gensphere(char type, int theta_subdivisions, int phi_subdivisions){

	//theta ranges across the entire sphere, from 0 - 2*pi (longitude - East/West)
	//phi ranges from -pi/2 to pi/2 (lattitude - North/South)

	if(theta_subdivisions < 3 || phi_subdivisions < 3){
		std::cout << "use more points in gensphere()" << endl << "try subdivision values of greater than 3 or 4" << endl;
		return -1;
	}

	std::vector<vec3> temp_points;

	int index = 0;

	int count_triangles = 0; //just out of curiousity

	float theta = 0;
	float theta_increment = (2*M_PI) / theta_subdivisions;

	float phi = -1 * (M_PI / 2);
	float phi_increment = M_PI / phi_subdivisions;

	switch (type){

		case "r":   //regular sphere

			for (int i = 0; i < phi_subdivisions; i++){

				for (int j = 0; j < theta_subdivisions; j++){

					temp_points[index] = vec3(cos(theta), sin(phi), sin(theta));
					index++;

					theta += theta_increment;
				}

				phi+=phi_increment;

			}

			id = regular_sphere;


			//from here to break - getting the points in the form of discrete triangles for glDrawArrays();
			int point1loc = 0;
			int point2loc = theta_subdivisions;
			int point3loc = point2loc + 1;

			points = new std::vector<vec3>;

			for (int k = 0; k < theta_subdivisions; k++){ //prepare the first row to be rendered as triangles
				//the issue keeping it from using the same function as the rest is that it only needs half of 
				//the number of triangles that the rest of the rows need -- this is also true of the last row

				points.push_back(temp_points[point1loc]);

				points.push_back(temp_points[point2loc]);
				point2loc++;

				points.push_back(temp_points[point3loc]);
				point3loc++;

				count_triangles++;

			}

			points.push_back(temp_points[0]);
			points.push_back(temp_points[point3loc - 1]);  //triangle that closes the gap between the first 
			points.push_back(temp_points[theta_subdivisions]); //and last triangles in the loop

			count_triangles++;

			point1loc = theta_subdivisions;
			point2loc = 2*theta_subdivisions;  //initialize for main body triangles
			point3loc = point2loc + 1;				//I have some drawings if anyones interested

			for(int l = 0; l < /*the number of triangles in the body of the sphere*/ ; l++){

				points.push_back(temp_points(point1loc));
				point1loc = (point1loc % theta_subdivisions) * l;

				points.push_back(temp_points[point2loc]); //first triangle of quad
				point2loc++;

				points.push_back(temp_points[point3loc]);
				point3loc++;

				count_triangles++;

				points.push_back(temp_points[point1loc]);
				point1loc++;
				points.push_back(temp_points[point1loc]); //second triangle of quad
				points.push_back(temp_points[point2loc]);

				count_triangles++;

			}

			point1loc = (phi_subdivisions - 2) * theta_subdivisions;
			point2loc =	point1loc + 1;
			point3loc = (phi_subdivisions - 1) * theta_subdivisions;

			for(int m = 0, m < theta_subdivisions; m++){
				points.push_back(temp_points[point1loc]);
				point1loc++;
				points.push_back(temp_points[point2loc]);
				point2loc++;
				points.push_back(temp_points[point3loc]);

				count_triangles++;

			}

			std::cout<< count_triangles << " triangles rendered by gensphere()" << endl;

			break;
 
		case "s":	//spiral sphere, kind of a helix - its an experiment, I thought it might be cool

			phi_increment = phi_increment / theta_subdivisions; //made smaller so that durring one revolution
				//itll be incrementally moving towards making a step of the same distance that would have been 
				//taken - the original phi increment

			for (int i = 0; i < phi_subdivisions; i++){

				for (int j = 0; j < theta_subdivisions; j++){

					temp_points[index1] = vec3(cos(theta), sin(phi), sin(theta));
					index1++;

					theta += theta_increment;
					phi+=phi_increment; //moved into the loop so as to make it easer to render as a strip
						//that is, the strip goes around the sphere like a helix that connects to itself
				}
				
			}

			id = spiral_sphere;

			points = new std::vector<vec3>;

			int pointloc1 = temp_points[0];
			int pointloc2 = temp_points[1];

			for(int k = 0; k < theta_subdivisions; k++){
				points.push_back(temp_points[pointloc1]);

				if(!(k < theta_subdivisions)){
					pointloc1 += 2; 	//first row doesnt get this - there are a few wasted triangles but its
										//only one draw call instead of three to split it up into fans and a strip
				}

				points.push_back(temp_points[pointloc2]);
				pointloc2 += 2;
			} 

			break;

		default:

			std::cout << "Please use a valid identifier when entering gensphere() parameters" << endl;
			std::cout << "You entered > \"" << type << "\"" << endl;
			std::cout << "The options are: " << endl;
			std::cout << " \"r\" - A regular sphere" << endl;
			std::cout << " \"s\" - A spiral sphere" << endl;

			return -1;
			id = error;

			break;

	}
}

void Object::perturb_surface(float roughness){

	srand(sizeof(points));

	for(int i = 0; i < points.size(); i++)
		points[i] += rand() * roughness * points[i]; 
}

void Object::genship(char type){
    switch(t){
		case "s": points = ship_spoints; break;
		case "m": points = ship_mpoints; break;
		case "l": points = ship_lpoints; break;
		default:
			std::cout << "Please use a valid identifier when entering genship() parameters" << endl;
			std::cout << "You entered > \"" << type << "\"" << endl;
			std::cout << "The options are: " << endl;
			std::cout << " \"s\" - A small ship" << endl;
			std::cout << " \"m\" - A medium ship" << endl;
			std::cout << " \"l\" - A large ship" << endl;

			break;
    }

    id = ship;

}

void Object::color_points(color c){

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
			std::cout << "Please use a valid identifier when using color_points() parameters" << endl;
    }

    for(int i = 0; i < points.size(); i++)
    	colors[i] = current_color;
//takes the color value and colors all points within the object and gives them all a solid color with that value
}

void Object::place_in_world(vec3 scale_factor, vec3 orientation, vec3 location){
	scale = scale_factor;
	orient = orientation;
	locate = location;
}