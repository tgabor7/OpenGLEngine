#pragma once

#include <iostream>
#include <GL\glew.h>
class Texture
{
public:
	Texture();
	Texture(const char* path);
	GLuint texture_id;
	GLuint speculatTexture;
	GLuint bloomMap;
	int reflectivity;
	int shineDamper;

	bool fakeLightning = false;

	~Texture();
};

