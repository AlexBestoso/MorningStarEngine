#version 330 core
in vec2 OtexturePos;

out vec4 FragColor;

uniform sampler2D menuTexture;

void main(){
	FragColor = texture(menuTexture, OtexturePos);
}
