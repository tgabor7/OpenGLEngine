#version 150

in vec3 position;

uniform mat4 transformation;
uniform mat4 view;
uniform mat4 projection;

out vec2 textureCoords;

void main(void){

	gl_Position = projection * view * transformation * vec4(position,1.0);
	
}