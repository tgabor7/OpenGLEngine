#pragma once
#include "System.h"
#include "Shader.h"
#include "Maths.h"
#include "Texture.h"
#include "ShadowFrameBuffer.h"
#include "Mesh.h"
#include "Light.h"
#include "InstanceRenderSystem.h"
#include "BillBoard.h"
#include "AnimatedMeshRenderer.h"
#include "CustomRenderSystem.h"
#include "ClothSystem.h"

class RenderSystem : public System
{
public:
	RenderSystem();
	void updateSystem(double delta);
	void updateComponents(double delta);
	static vector<CustomRenderSystem*> custom_renderer;
	~RenderSystem();
private:
	void setupTexture(GLuint *texture);
	void renderBillBoards(vector<BillBoard> billboards);
	void renderShadow(std::vector<Mesh> models, std::vector<Light> lights);
	void renderShadow(std::vector<AnimatedMesh> models, std::vector<Light> lights);
	Shader shader;
	Shader background_shader;
	Shader shadow_shader;
	Shader billboard_shader;
	AnimatedShader anim_shadow_shader;
	Texture *texture;
	std::vector<ShadowFrameBuffer> fbos;
	vector<float> vertices = { -1,1,1,1,-1,-1, //first triangle
		1,1,1,-1,-1,-1 //second triangle
	};
	void drawBackground();
	GLuint vao;
	InstanceRenderSystem instanceRenderer;
	AnimatedMeshRenderer animationRenderer;
	ClothSystem cloth_renderer;
};

