attribute vec4 vPosition;
attribute vec4 vColor;

uniform mat4 transform;
uniform mat4 camera;

void main(){
	gl_FragColor = vColor;
}