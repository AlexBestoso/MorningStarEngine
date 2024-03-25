#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec2 texturePos;
layout (location = 2) in vec3 aNormal;
layout (location = 3) in vec3 aColor;

out vec2 oTexturePos;
out vec3 FragPos;
out vec3 Normal;
out vec4 bColor;

//uniform mat4 transform;
uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main(){
   	gl_Position = projection * view * model * vec4(aPos, 1.0);
	oTexturePos = vec2(texturePos.x, texturePos.y);
	FragPos = vec3(model * vec4(aPos, 1.0));
	Normal = mat3(transpose(inverse(model))) * aNormal;
	bColor = vec4(aColor, 1.0);
}
