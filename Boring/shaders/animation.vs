#version 150

in vec3 in_position;
in vec2 in_textureCoords;
in vec3 in_normal;
in ivec4 in_jointIndices;
in vec4 in_weights;


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
uniform mat4 jointTransforms[50];


uniform float useFakeLightning;
uniform int numberOfLights;


void main(){

	Normal = transpose(inverse(mat3(transformation)))*in_normal;
	vec4 worldPosition = transformation * vec4(in_position,1.0);
	vec4 totalLocalPos = vec4(0.0);
	vec4 totalNormal = vec4(0.0);
	tex_coords = in_textureCoords;
	
	for(int i=0;i<4;i++){
		
		mat4 jointTransform = jointTransforms[in_jointIndices[i]];
		vec4 posePosition = jointTransform * vec4(in_position, 1.0);
		totalLocalPos += posePosition * in_weights[i];
			
		vec4 worldNormal = jointTransform * vec4(in_normal, 0.0);
		totalNormal += worldNormal * in_weights[i];
			
		
	}
	gl_Position = projection* view * transformation * totalLocalPos;
	
	
	vec3 actualNormal = in_normal;
	if(useFakeLightning > 0.5){
		actualNormal = vec3(1.0,1.0,1.0);
	}
	vec3 pos = vec3(transformation * vec4(in_position,1.0));
	surfaceNormal = (transformation * vec4(actualNormal,0.0)).xyz;
	for(int i = 0;i<numberOfLights;i++){
	toLightVector[i] = lightPosition[i] - worldPosition.xyz;
	}
	toCameraVector = (inverse(view) * vec4(0.0,0.0,0.0,1.0)).xyz -worldPosition.xyz;
	for(int i = 0;i<numberOfLights;i++){
		FragPosLightSpace[i] = lightSpaceMatrix[i] * vec4(pos,1.0);
	}
	
}