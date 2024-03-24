#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec2 texturePos;
layout (location = 2) in vec3 normalPos;

out vec2 OtexturePos;

uniform mat4 model;

void main(){
   	gl_Position = vec4(aPos, 1.0)*model;
	OtexturePos = vec2(texturePos.x, texturePos.y);
}
