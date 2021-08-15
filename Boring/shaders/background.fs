#version 330

in vec2 tex_coords;


uniform sampler2D sampler;

layout (location = 0) out vec4 FragColor;
layout (location = 2) out vec4 out_DistColor;

void main(void){
	
	vec4 color = texture(sampler,tex_coords);
	
	FragColor = color;
	out_DistColor = vec4(0.0);
}