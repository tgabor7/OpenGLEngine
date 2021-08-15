#version 150

in vec3 vertices;
in vec3 normal;
in vec2 textures;

out vec4 FragPos;
out vec3 Normal;
out vec2 TexCoords;
out vec4 FragPosLightSpace;

uniform mat4 lightSpaceMatrix;
uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;


void main(){
	
	 
	TexCoords = textures;
	
	gl_Position =  lightSpaceMatrix * model * vec4(vertices, 1.0f);
	
}
