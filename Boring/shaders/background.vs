#version 150

in vec2 vertices;

out vec2 tex_coords;

void main(void){

	gl_Position = vec4(vertices,0.0,1.0);
	vec2 centerTexCoords = vertices * 0.5 + 0.5;
	tex_coords = centerTexCoords;
	
	
}