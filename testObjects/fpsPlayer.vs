#version 330 core
layout (location = 0) in vec3 locationPos;

uniform mat4 fpsview;
uniform mat4 fpsperspective;

void main(){
	gl_Position = fpsperspective * fpsview * vec4(locationPos, 1.0f);
}
