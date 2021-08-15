#pragma once
#include "CustomRenderSystem.h"
#include "Shader.h"

class CustomInstanceRenderer : public CustomRenderSystem
{
public:
	CustomInstanceRenderer();
	Shader shader;
	void render();
	~CustomInstanceRenderer();
};

