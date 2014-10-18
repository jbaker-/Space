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

			phi_increment = phi_increment / theta_subdivisions; //made smaller and incremented in the inner loop 
				//so that durring one revolution itll be incrementally moving towards making a step of the same 
				//distance that would have been taken in the outer loop - the regular sphere's phi increment

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

			//Output points as triangle strip - this may need to be rewritten better

			points = new std::vector<vec3>;

			std::vector::iterator pointloc1 = temp_points.begin(); //higher up the sphere
			std::vector::iterator pointloc2 = temp_points.begin(); //lower down the sphere (one row lower)

			points.push_back(*pointloc1);
			points.push_back(*pointloc1); //initiate the triangle strip, this'd be easier as a fan but
			points.push_back(*pointloc1); //the goal is to have it just be one draw call	

			pointloc2++;

			for(int k = 0; k < theta_subdivisions; k++){
				points.push_back(*pointloc2);
				pointloc2++;		//the triangle strip equivalent to a triangle fan
				points.push_back(*pointloc1);
			} 

			for(int l = 0; l < ((phi_subdivisions - 2) * theta_subdivisions); l++){
				points.push_back(*pointloc2);
				pointloc2++;
				points.push_back(*pointloc1); //main body of the sphere - everything but the two ends
				pointloc2++;
			}

			pointloc2 = temp_points.end();

			for(int m = 0; m < theta_subdivisions; m++){
				points.push_back(*pointloc1);

				if(pointloc1 < pointloc2){
					pointloc1++;
				}

				points.push_back(*pointloc2);
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
		case "s": points = new std::vector<vec3>(ship_spoints, ship_spoints + sizeof(ship_spoints) / sizeof(vec3)); break;
		case "m": points = new std::vector<vec3>(ship_mpoints, ship_mpoints + sizeof(ship_mpoints) / sizeof(vec3)); break;
		case "l": points = new std::vector<vec3>(ship_lpoints, ship_lpoints + sizeof(ship_lpoints) / sizeof(vec3)); break;
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

void Object::color_points(color c, bool rand, float weight){

	if(weight < 0){
		std::cout << "Please use a postiive value when entering weight for color_points()" << endl;
		return;
	}

	if(points == NULL){
		std::cout << "No points found, color_points() exited" << endl;
		return;
	}

	if(colors != NULL){
		delete colors;

		colors = new std::vector<vec3>;
	}

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

    if(rand){

	    srand(sizeof(colors));

	    for (int i = 0; i < points.size(); i++){
	    	colors.push_back(new vec3( current_color.x * 1/rand(), current_color.y * 1/rand(), current_color.z =  ))
	    }


	}else{

    	for(int i = 0; i < points.size(); i++)
    		colors.push_back(current_color);

	}

//takes the color value and colors all points within the object and gives them all a solid color with that value

}

void Object::place_in_world(vec3 scale_factor, vec3 orientation, vec3 location){
	scale = scale_factor;
	orient = orientation;
	locate = location;
}