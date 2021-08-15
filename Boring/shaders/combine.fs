#version 150

in vec2 textureCoords;

out vec4 out_Color;

uniform sampler2D colourTexture;
uniform sampler2D highlightTexture;
uniform float intensity;

void main(void){

	vec4 sceneColour = texture(colourTexture,textureCoords);
	vec4 highlightColour = texture(highlightTexture,textureCoords);
	
	vec4 color;
	
	color = (sceneColour + highlightColour);
	
	
	out_Color = color;
	
}