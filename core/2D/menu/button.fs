#version 330 core
in vec2 tPosFrag;
in vec4 extraColorFrag;

out vec4 FragColor;

uniform sampler2D buttonTexture;
uniform int textureActive;

void main(){
	if(textureActive == 1){
		FragColor = texture(buttonTexture, tPosFrag) + extraColorFrag;
	}else{
		FragColor = extraColorFrag;
	}
}
