#version 330

in vec2 tex_coords;
in float o;

uniform sampler2D sampler;
uniform vec4 custom_color;

layout (location = 0) out vec4 FragColor;
layout (location = 2) out vec4 out_DistColor;

void main(){

	vec4 color = texture2D(sampler,tex_coords);
	
	if(color.a < .5) discard;
	if(custom_color.a > 0){
		FragColor = vec4(o,o,o,1) * custom_color;
	}else{
		FragColor = color;
	}
	out_DistColor = vec4(0,0,0,1);
}