#version 330 core
layout (points) in;
layout (line_strip, max_vertices = 6) out;

in vec4 color[];
out vec4 fcolor;

uniform float testing;
uniform float sWidth;
uniform float sHeight;
uniform float sCentW;
uniform float sCentH;

void setVtx(vec4 vtx){
	vec4 persp = vec4(testing, testing, testing, testing);	
	gl_Position = (gl_in[0].gl_Position + vtx*persp);
}
void main() {
	fcolor = color[0];
    	setVtx(vec4(-1.0, 0.0, 0.0, 0.0));
    	EmitVertex();
    	setVtx(vec4(1.0, 0.0, 0.0, 0.0));
    	EmitVertex();
	EndPrimitive();

//
    	setVtx(vec4(0.0, -1.0, 0.0, 0.0));
    	EmitVertex();
    	setVtx(vec4(0.0, 1.0, 0.0, 0.0));
    	EmitVertex();
	EndPrimitive();
//
    	setVtx(vec4(1.0, 1.0, 0.0, 0.0));
    	EmitVertex();
    	setVtx(vec4(-1.0, -1.0, 0.0, 0.0));
    	EmitVertex();
	EndPrimitive();
//
}  
