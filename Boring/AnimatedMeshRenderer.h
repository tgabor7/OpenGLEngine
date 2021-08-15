#pragma once
#include "AnimatedShader.h"
#include "Maths.h"
#include "AnimatedMesh.h"
#include "Light.h"
#include "ShadowFrameBuffer.h"

class AnimatedMeshRenderer
{
public:
	AnimatedMeshRenderer();
	void render(vector<AnimatedMesh> models,vector<Light> lights,vector<ShadowFrameBuffer> fbos);
	~AnimatedMeshRenderer();
private:
	AnimatedShader shader;
	mat4x4 projection;
	mat4x4 mat[50];
};

