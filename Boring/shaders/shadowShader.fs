#version 150


in vec4 FragPos;
in vec3 Normal;
in vec2 TexCoords;


uniform sampler2D shadowMap;

out vec4 FragColor;



void main(void){
	
		
		vec4 color = texture2D(shadowMap,TexCoords);
   		
   		if(color.a < 0.5)
   			discard;
   		FragColor = vec4(0);
  
}