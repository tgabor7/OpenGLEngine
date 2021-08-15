#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <fstream>
#include "AnimatedShader.h"
#include <vector>
#include <glm\mat4x4.hpp>
#include <glm\gtc\type_ptr.hpp>

using namespace std;



AnimatedShader::AnimatedShader() {}
AnimatedShader::AnimatedShader(std::string path)
{
	// Create the shaders
	GLuint VertexShaderID = glCreateShader(GL_VERTEX_SHADER);
	GLuint FragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);

	// Read the Vertex AnimatedShader code from the file
	std::string VertexShaderCode;
	std::ifstream VertexShaderStream(path + ".vs", std::ios::in);
	if (VertexShaderStream.is_open()) {
		std::string Line = "";
		while (getline(VertexShaderStream, Line))
			VertexShaderCode += "\n" + Line;
		VertexShaderStream.close();
	}
	else {
		printf("Impossible to open %s. Are you in the right directory ?\n", (path + ".vs").c_str());
		getchar();

	}

	// Read the Fragment AnimatedShader code from the file
	std::string FragmentShaderCode;
	std::ifstream FragmentShaderStream(path + ".fs", std::ios::in);
	if (FragmentShaderStream.is_open()) {
		std::string Line = "";
		while (getline(FragmentShaderStream, Line))
			FragmentShaderCode += "\n" + Line;
		FragmentShaderStream.close();
	}

	GLint Result = GL_FALSE;
	int InfoLogLength;


	// Compile Vertex AnimatedShader
	printf("Compiling shader : %s\n", (path + ".vs").c_str());
	char const * VertexSourcePointer = VertexShaderCode.c_str();
	glShaderSource(VertexShaderID, 1, &VertexSourcePointer, NULL);
	glCompileShader(VertexShaderID);

	// Check Vertex AnimatedShader
	glGetShaderiv(VertexShaderID, GL_COMPILE_STATUS, &Result);
	glGetShaderiv(VertexShaderID, GL_INFO_LOG_LENGTH, &InfoLogLength);
	if (InfoLogLength > 0) {
		std::vector<char> VertexShaderErrorMessage(InfoLogLength + 1);
		glGetShaderInfoLog(VertexShaderID, InfoLogLength, NULL, &VertexShaderErrorMessage[0]);
		printf("%s\n", &VertexShaderErrorMessage[0]);
	}



	// Compile Fragment AnimatedShader
	printf("Compiling shader : %s\n", (path + ".fs").c_str());
	char const * FragmentSourcePointer = FragmentShaderCode.c_str();
	glShaderSource(FragmentShaderID, 1, &FragmentSourcePointer, NULL);
	glCompileShader(FragmentShaderID);

	// Check Fragment AnimatedShader
	glGetShaderiv(FragmentShaderID, GL_COMPILE_STATUS, &Result);
	glGetShaderiv(FragmentShaderID, GL_INFO_LOG_LENGTH, &InfoLogLength);
	if (InfoLogLength > 0) {
		std::vector<char> FragmentShaderErrorMessage(InfoLogLength + 1);
		glGetShaderInfoLog(FragmentShaderID, InfoLogLength, NULL, &FragmentShaderErrorMessage[0]);
		printf("%s\n", &FragmentShaderErrorMessage[0]);
	}



	// Link the program
	printf("Linking program\n");
	program = glCreateProgram();
	glAttachShader(program, VertexShaderID);
	glAttachShader(program, FragmentShaderID);

	glBindAttribLocation(program, 0, "in_position");
	glBindAttribLocation(program, 1, "in_textureCoords");
	glBindAttribLocation(program, 2, "in_normal");
	glBindAttribLocation(program, 3, "in_jointIndices");
	glBindAttribLocation(program, 4, "in_weights");

	glLinkProgram(program);

	// Check the program
	glGetProgramiv(program, GL_LINK_STATUS, &Result);
	glGetProgramiv(program, GL_INFO_LOG_LENGTH, &InfoLogLength);
	if (InfoLogLength > 0) {
		std::vector<char> ProgramErrorMessage(InfoLogLength + 1);
		glGetProgramInfoLog(program, InfoLogLength, NULL, &ProgramErrorMessage[0]);
		printf("%s\n", &ProgramErrorMessage[0]);
	}

	glValidateProgram(program);





}
void AnimatedShader::bind() {
	glUseProgram(program);
}
void AnimatedShader::unBind() {
	glUseProgram(0);
}
void AnimatedShader::setUniform(const char* name, glm::mat4x4 value) {
	int location = glGetUniformLocation(program, name);
	if (location != -1)
		glUniformMatrix4fv(location, 1, false, glm::value_ptr(value));
}
void AnimatedShader::setUniform(const char* name, glm::vec4 value) {
	int location = glGetUniformLocation(program, name);
	if (location != -1)
		glUniform4f(location, value.x, value.y, value.z, value.w);
}
void AnimatedShader::setUniform(const char* name, glm::vec3 value) {
	int location = glGetUniformLocation(program, name);
	if (location != -1)
		glUniform3f(location, value.x, value.y, value.z);
}
void AnimatedShader::setUniform(const char* name, int value) {
	int location = glGetUniformLocation(program, name);
	if (location != -1)
		glUniform1i(location, value);
}
void AnimatedShader::setUniform(const char* name, float value) {
	int location = glGetUniformLocation(program, name);
	if (location != -1)
		glUniform1f(location, value);
}
void AnimatedShader::setUniform(std::string name, glm::vec3* values) {

	glUniform3fv(glGetUniformLocation(program, name.c_str()), 4,
		glm::value_ptr(values[0]));


}
void AnimatedShader::setUniform(std::string name, glm::mat4x4* values) {
	glUniformMatrix4fv(glGetUniformLocation(program, name.c_str()), 50,
		false, glm::value_ptr(values[0]));

}
void AnimatedShader::setUniform(std::string name, glm::mat4x4* values, int count) {
	glUniformMatrix4fv(glGetUniformLocation(program, name.c_str()), count,
		false, glm::value_ptr(values[0]));

}
std::string AnimatedShader::readFile(char* path) {
	std::string VertexShaderCode;
	std::ifstream VertexShaderStream(path, std::ios::in);
	if (VertexShaderStream.is_open()) {
		std::string Line = "";
		while (getline(VertexShaderStream, Line))
			VertexShaderCode += "\n" + Line;
		VertexShaderStream.close();
	}
	else {
		printf("Impossible to open %s. Are you in the right directory ? Don't forget to read the FAQ !\n", path);
	}
	cout << VertexShaderCode;
	return VertexShaderCode;
}

AnimatedShader::~AnimatedShader()
{
}
