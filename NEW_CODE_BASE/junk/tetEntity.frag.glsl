#version 330 core
in float magic;
in vec4 fcolor;

out vec4 FragColor;

uniform float testing;

void main()
{
	FragColor = fcolor;//vec4(1.0, 0.0, 0.0, 1.0f);
}
