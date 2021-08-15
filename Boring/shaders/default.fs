#version 330

out vec4 out_colour;

in vec2 textureCoords;

uniform sampler2D originalTexture;

uniform int width;
uniform int height;

layout (location = 1) out vec4 out_BrightColor;


void main(void){	
	vec4 color = texture2D(originalTexture,textureCoords);
	
	out_colour = color*0.9f;
	
}
