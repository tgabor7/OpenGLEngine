#version 150

in vec3 vertices;
in mat4 transformation;

out vec2 tex_coords;

uniform mat4 projection;

void main(void){

	gl_Position = projection * transformation * vec4(vertices,1.0);
	vec2 centerTexCoords = vec2(vertices.x,vertices.y) * 0.5 + 0.5;
	tex_coords = centerTexCoords;
	
	
}