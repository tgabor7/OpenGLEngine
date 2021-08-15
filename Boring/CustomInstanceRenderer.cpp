#include "CustomInstanceRenderer.h"
#include <iostream>


CustomInstanceRenderer::CustomInstanceRenderer()
{
	shader = Shader("shaders/instance");
}
void CustomInstanceRenderer::render()
{
	//std::cout << "asdasdasd \n";
}

CustomInstanceRenderer::~CustomInstanceRenderer() 
{
}
