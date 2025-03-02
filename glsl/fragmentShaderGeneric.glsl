#version 330 core

in vec3 FragPos;
in vec4 bColor;

out vec4 FragColor;

void main(){
	FragColor = bColor;
}
