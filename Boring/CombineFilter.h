#include "FrameBuffer.h"
#include "OBJLoader.h"
#include "DataTypes.h"
#include "Texture.h"
#include "Shader.h"
#include "EntityHandler.h"

class CombineFilter
{

public:
	CombineFilter() {}
	CombineFilter(const char* path);
	void render(GLuint texture0, GLuint texture1);
	FrameBuffer fbo;

	GLuint v;

private:

	vector<float> vertices;

	Shader shader;

};