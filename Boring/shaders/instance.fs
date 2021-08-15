#version 330


in vec2 tex_coords;
in float d;
uniform sampler2D sampler;


layout (location = 0) out vec4 FragColor;
layout (location = 1) out vec4 out_BrightColor;
	

void main(){

		vec4 color = texture2D(sampler,tex_coords);
		

		FragColor = color;
		out_BrightColor = vec4(0.0);
		
		
		FragColor = vec4(1);
}
