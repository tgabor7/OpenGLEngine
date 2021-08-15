#version 330

in vec2 tex_coords;


uniform sampler2D sampler;
uniform sampler2D distMap;

layout (location = 2) out vec4 out_DistColor;
layout (location = 0) out vec4 out_color;

void main()
{
	vec4 color = texture2D(sampler,tex_coords);
	out_color = color;
	out_DistColor = vec4(0,0,0,1);
}