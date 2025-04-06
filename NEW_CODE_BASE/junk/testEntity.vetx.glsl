#version 330 core
layout (location = 0) in vec2 aPos;

uniform float testing;
void main()
{
	vec2 newPos = aPos + vec2(testing, 0);
	gl_Position = vec4(newPos, 0.0, 1.0);
	
}
