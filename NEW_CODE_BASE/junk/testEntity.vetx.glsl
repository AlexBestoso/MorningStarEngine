#version 330 core
layout (location = 0) in float aPos;

uniform float testing;
void main()
{
	vec2 newPos = vec2(aPos, aPos+0.12);// + vec2(testing, 0);
	gl_Position = vec4(newPos, 0.0, 1.0);
	
}
