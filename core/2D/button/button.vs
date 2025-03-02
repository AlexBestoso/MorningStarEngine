#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec2 tPos;
layout (location = 2) in vec3 nPos;

out vec2 tPosFrag;
out vec4 extraColorFrag;

uniform mat4 model;
uniform vec3 extraColor;
uniform vec2 mousePos;
uniform int hovered;

void main(){
	gl_Position = model*vec4(aPos, 1.0);
	tPosFrag = tPos;
	if(hovered == 1){
		extraColorFrag = vec4(0.5, 0.5, 0.5, 1.0);
	}else{
		extraColorFrag = vec4(extraColor, 1.0);
	}
}
