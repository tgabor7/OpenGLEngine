#version 150

in vec3 vertices;
in vec2 textures;
in vec3 normal;


out vec2 tex_coords;


uniform mat4 projection;
uniform mat4 transformation;
uniform mat4 view;
uniform float scale;
uniform int rows;
uniform int columns;
uniform vec2 pointer;

void main(){

	
	vec4 worldPosition = transformation * vec4(vertices,1.0);
	tex_coords = textures/vec2(rows,columns);
	tex_coords+=pointer*(1.0/vec2(rows,columns));
	
	
	gl_Position = projection * transformation * vec4(vertices,1.0);
	
}