#version 150

in vec2 tex_coords;

out vec4 out_colour;

uniform sampler2D sampler;

void main(void){
	
	vec4 color = texture(sampler,tex_coords);
	if(color.a < .5) discard;
	out_colour = color;
	
}