#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec2 texturePos;
layout (location = 2) in vec3 normalizedPos;

out vec2 GTexturePos;
out vec3 FragPos;
out vec3 Normalized;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main(){
        gl_Position = projection * view * model * vec4(aPos, 1.0);
        GTexturePos = texturePos;
	FragPos = vec3(model * vec4(aPos, 1.0));
	Normalized = mat3(transpose(inverse(model))) * normalizedPos;
}
