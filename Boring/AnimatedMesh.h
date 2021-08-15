#pragma once
#include "Texture.h"
#include "DataTypes.h"
#include "EntityHandler.h"
#include <glm\vec3.hpp>
#include "Animation.h"

using namespace glm;

class AnimatedMesh : public Component<AnimatedMesh>
{
public:
	AnimatedMesh();
	AnimatedMesh(vec3 position, ModelData *data, Animation animation, vec3 transformation, Texture *texture);
	Animation animation;
	vector<Bone> bones;
	int VertexArrayID;
	Texture *texture;
	void prepare();
	void render();
	void unBind();
	int draw_count;
	bool outline = false;
	bool culling = false;
	vec3 position;
	vec3 transformation;
	vec3 rotation;
	vec4 customColor;
	ModelData *data;
	void setFrame(int i);
	~AnimatedMesh();

};

