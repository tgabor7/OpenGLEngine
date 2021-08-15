#version 150

in vec3 vertices;
in vec2 textures;
in vec3 normal;


out vec2 tex_coords;
out vec3 surfaceNormal;
out vec3 toLightVector[4];
out vec3 toCameraVector;
out vec4 FragPosLightSpace[4];
out vec3 Normal;


uniform mat4 projection;
uniform mat4 transformation;
uniform mat4 view;
uniform mat4 shadowView;
uniform vec3 lightPosition[4];
uniform mat4 lightSpaceMatrix[4];
uniform int rows;
uniform int columns;
uniform vec2 pointer;

uniform float useFakeLightning;
uniform int numberOfLights;

void main(){

	Normal = transpose(inverse(mat3(transformation)))*normal;
	
	vec4 worldPosition = transformation * vec4(vertices,1.0);
	tex_coords = textures/vec2(rows,columns);
	tex_coords+=pointer*(1.0/vec2(rows,columns));
	gl_Position =  projection * view * worldPosition;
	
	vec3 actualNormal = normal;
	if(useFakeLightning > 0.5){
		actualNormal = vec3(1.0,1.0,1.0);
	}
	vec3 pos = vec3(transformation * vec4(vertices,1.0));
	surfaceNormal = (transformation * vec4(actualNormal,0.0)).xyz;
	for(int i = 0;i<numberOfLights;i++){
	toLightVector[i] = lightPosition[i] - worldPosition.xyz;
	}
	toCameraVector = (inverse(view) * vec4(0.0,0.0,0.0,1.0)).xyz -worldPosition.xyz;
	for(int i = 0;i<numberOfLights;i++){
		FragPosLightSpace[i] = lightSpaceMatrix[i] * vec4(pos,1.0);
	}
	
}