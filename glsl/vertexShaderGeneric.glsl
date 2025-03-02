#version 330 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColor;

out vec3 FragPos;
out vec4 bColor;


void main(){
   	gl_Position = vec4(aPos, 1.0);
	FragPos = vec3(vec4(aPos, 1.0));
	bColor = vec4(aColor, 1.0);
}
