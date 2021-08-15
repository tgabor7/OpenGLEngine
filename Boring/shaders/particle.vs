#version 330

in vec3 vertices;
in vec2 textures;
in vec3 transformation;
in vec3 scale;
in vec3 rotation;
in vec3 normal;
in float life;

out vec2 tex_coords;
out float o;

uniform float billboard;
uniform mat4 view;
uniform mat4 projection;
uniform int rows = 2;
uniform int columns = 2;
uniform sampler2D sampler;
uniform sampler2D positiontexture;

mat4 rotatey(mat4 m){

	mat4 result = m;
	float cosy = cos(rotation.y);
	float siny = sin(rotation.y);
	float rm00 = cosy;
	float rm02 = -siny;
	float rm20 = siny;
	float rm22 = cosy;
	
	result[0][0] = m[0][0] * rm00 + m[2][0] * rm02;
	result[0][1] = m[0][1] * rm00 + m[2][1] * rm02;
	result[0][2] = m[0][2] * rm00 + m[2][2] * rm02;
	result[0][3] = m[0][3] * rm00 + m[2][3] * rm02;
	
	result[2][0] = m[0][0] * rm20 + m[2][0] * rm22;
	result[2][1] = m[0][1] * rm20 + m[2][1] * rm22;
	result[2][2] = m[0][2] * rm20 + m[2][2] * rm22;
	result[2][3] = m[0][3] * rm20 + m[2][3] * rm22;
	
	return result;
}
void main(){

	
	o = (2 - life)/2;
	
	float pointer;
	
	pointer = int((life/5)*rows*columns);
	
	vec2 p;
	p.x = mod(pointer,columns);
	p.y = int(pointer/columns);
	
	tex_coords = textures/vec2(columns,rows);
	
	tex_coords+=p*1.0/vec2(columns,rows);
	
	mat4 matrix = mat4(	1,0,0,0,
						0,1,0,0,
						0,0,1,0,
						transformation.x,transformation.y,transformation.z,1);
	matrix = rotatey(matrix);
	matrix[0]*=scale.x;
	matrix[1]*=scale.y;
	matrix[2]*=scale.z;
	
	vec4 localpos = vec4(vertices,1.0);
	if(billboard > .5){
		matrix *= inverse(view);		
	}
	
	gl_Position = projection * view * matrix * localpos;

}
