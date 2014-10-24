attribute vPosition;
attribute vColor;

uniform mat4 transform;
uniform mat4 camera;

void main(){
	gl_FragColor = vColor;
}