#include "CustomRenderSystem.h"
#include "RenderSystem.h"


CustomRenderSystem::CustomRenderSystem()
{
	RenderSystem::custom_renderer.push_back(this);
}


CustomRenderSystem::~CustomRenderSystem()
{
}
