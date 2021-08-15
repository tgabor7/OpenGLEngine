#version 150

in vec3 vertices;

uniform mat4 transformation;
uniform mat4 view;
uniform mat4 projection;
uniform vec3 offset;

void main()
{
    gl_Position = projection * view * transformation * vec4(vertices+offset,1.0);
}