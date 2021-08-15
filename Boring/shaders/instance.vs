#version 300 es

in vec3 vertices;
in vec2 textures;
in vec3 normal;
in mat4 transformation;


out vec2 tex_coords;
out float d;


uniform mat4 projection;
uniform mat4 view;

uniform float useFakeLightning;


void main(void){


    mat4 mvp = mat4(1,0,0,0,0,1,0,0,0,0,1,0,0,0,0,1);

	gl_Position = projection*view*transformation*vec4(vertices,1.0);
    tex_coords = textures;
	d = transformation[0];

}