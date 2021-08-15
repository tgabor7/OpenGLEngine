#include <GL\glew.h>
#include <glm\mat4x4.hpp>
#include <string>
#include <vector>
#pragma once

using namespace std;


class Shader
{
public:
	Shader();
	Shader(std::string path);
	Shader(string path,vector<pair<int,string>> attributes);
	std::string readFile(char* path);
	GLuint program;
	void bind();
	void unBind();
	void setUniform(const char* name, glm::mat4x4 value);
	void setUniform(const char* name, glm::vec4 value);
	void setUniform(const char* name, glm::vec3 value);
	void setUniform(const char* name, glm::vec2 value);

	void bindAttribLocation(int n, char* name);

	void setUniform(const char* name, int value);
	void setUniform(const char* name, float value);
	void setUniform(std::string name, glm::vec3* value);
	void setUniform(std::string name, glm::mat4x4* value);
	~Shader();
};

