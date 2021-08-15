#version 330

uniform sampler2D sampler;
uniform sampler2D shadowMap[4];
uniform sampler2D specularMap;
uniform sampler2D distMap;
uniform float usesSpecularMap;
uniform float usesDistMap;
uniform vec3 lightColor[4];
uniform vec3 attenuation[4];
uniform float shineDamper;
uniform float reflectivity;
uniform vec4 outLineColor;
uniform int numberOfLights;
uniform float useFakeLightning;
uniform vec4 customColor;

in vec2 tex_coords;
in vec3 surfaceNormal;
in vec3 toLightVector[4];
in vec3 toCameraVector;
in vec4 FragPosLightSpace[4];
in vec3 Normal;

layout (location = 0) out vec4 FragColor;
layout (location = 1) out vec4 out_BrightColor;
layout (location = 2) out vec4 out_DistColor;
layout (location = 3) out vec4 test_color;



float ShadowCalculation(vec4 fragPosLightSpace[4]){
  
 	float totalShadow = 0.0;
	for(int i = 0;i<numberOfLights;i++){
		float bias = max(0.005 * (1-dot(surfaceNormal,toLightVector[i])), 0.0005);
		
		vec4 lSpace = fragPosLightSpace[i];
		
	    vec3 projCoords = lSpace.xyz / lSpace.w;
	    
	
	     	
	    projCoords = projCoords * 0.5 + 0.5;
	   
	  
	  
	    float closestDepth = texture(shadowMap[i], projCoords.xy).r; 
	   
	    float currentDepth = projCoords.z;
	   	
	   
	   
	    float shadow = currentDepth - bias > closestDepth ? 1.0 : 0.0;
		
		
		 
		    shadow = 0.0;
		    vec2 texelSize = 1.0 / textureSize(shadowMap[i], 0);
			for(int x = -1; x <= 1; ++x)
				{
	   		for(int y = -1; y <= 1; ++y)
	   			{
	        float pcfDepth = texture(shadowMap[i], projCoords.xy + vec2(x, y) * texelSize).r; 
	        shadow += currentDepth - bias > pcfDepth ? 1.0 : 0.0;
	               
	  		 	}    
				}
		shadow /= 5.0;
		       
		if(projCoords.z > 1.0)
	        shadow = 0.0;
		
		if(dot(surfaceNormal,toLightVector[i]) <= .5)
	    	shadow = 1;
	    totalShadow = totalShadow + shadow;
	
	}
	
    return totalShadow;
     
    
    

    
	}

void main(){

		
		vec3 unitNormal = normalize(surfaceNormal);
		vec3 unitVectorToCamera = normalize(toCameraVector);
		
		vec3 totalDiffuse = vec3(0.0);
		vec3 totalSpecular = vec3(0.0);
		float shadow = ShadowCalculation(FragPosLightSpace);
		
		for(int i = 0;i<numberOfLights;i++){
			float distance = length(toLightVector[i]);
			float attFactor = attenuation[i].x + (attenuation[i].y * distance) + (attenuation[i].z * distance * distance);
			vec3 unitLightVector = normalize(toLightVector[i]);
			
			float nDot1 = dot(unitNormal,unitLightVector);
			float brightness = max(nDot1,0);
			
			totalDiffuse = totalDiffuse+(brightness * lightColor[i])/attFactor;
			
			
			vec3 lightDirection = -unitLightVector;
			vec3 reflectedLightDirection  = reflect(lightDirection,unitNormal);
			
			float specularFactor = dot(reflectedLightDirection,unitVectorToCamera);
			specularFactor = max(specularFactor,0.0);
			float dampedFactor = pow(specularFactor,shineDamper);
			totalSpecular = totalSpecular+(dampedFactor * lightColor[i])/attFactor;
		}
		totalDiffuse = max(totalDiffuse,0.2);
		
		vec4 textureColor = texture2D(sampler, tex_coords);

		
	
		if(customColor.a>0.0){
		textureColor = customColor;
		}
		
		
	
	
	
		out_BrightColor = vec4(0.0);
		out_DistColor = vec4(0,0,0,1);
		test_color = vec4(0.0);
		
		
		vec4 mapInfo = texture(specularMap,tex_coords);
		totalSpecular*=mapInfo.r;
		if(mapInfo.g > 0.5){
			out_BrightColor = textureColor + vec4(totalSpecular,1.0);
			
			totalSpecular = vec3(1.0);
		}
		
		
		vec4 mapInfo1 = texture(distMap,tex_coords);
		totalSpecular*=mapInfo1.r;
		if(mapInfo1.g > 0.5){
			out_DistColor = textureColor;
			test_color = textureColor;
			totalSpecular = vec3(1.0);
		}
		
		
		vec4 color =  vec4(totalDiffuse,textureColor.a) * (textureColor + vec4(totalSpecular,1.0))*(1-shadow*0.7f);
		color.a = 1.0;
		
	
		
		
		if(outLineColor.a > 0){
		FragColor = outLineColor;
		}else if(useFakeLightning!=0.0){
		FragColor = textureColor;
		}else{
		FragColor = color;
		}
		
		
}
