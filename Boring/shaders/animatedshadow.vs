#version 150

in vec3 in_position;
in vec2 in_textureCoords;
in vec3 in_normal;
in ivec4 in_jointIndices;
in vec4 in_weights;


out vec2 TexCoords;
out vec3 surfaceNormal;
out vec3 toLightVector[4];
out vec3 toCameraVector;
out vec4 FragPosLightSpace[4];
out vec3 Normal;


uniform mat4 projection;
uniform mat4 model;
uniform mat4 view;
uniform mat4 shadowView;
uniform vec3 lightPosition[4];
uniform mat4 lightSpaceMatrix;
uniform mat4 jointTransforms[50];


uniform float useFakeLightning;
uniform int numberOfLights;


void main(){

	Normal = transpose(inverse(mat3(model)))*in_normal;
	vec4 worldPosition = model * vec4(in_position,1.0);
	vec4 totalLocalPos = vec4(0.0);
	vec4 totalNormal = vec4(0.0);
	TexCoords = in_textureCoords;
	
	for(int i=0;i<4;i++){
		
		mat4 jointTransform = jointTransforms[in_jointIndices[i]];
		vec4 posePosition = jointTransform * vec4(in_position, 1.0);
		totalLocalPos += posePosition * in_weights[i];
			
		vec4 worldNormal = jointTransform * vec4(in_normal, 0.0);
		totalNormal += worldNormal * in_weights[i];
			
		
	}
	gl_Position = lightSpaceMatrix * model * totalLocalPos;
	
	
	
}