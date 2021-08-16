#include "Mesh.h"
#include "TestState.h"
#include "System.h"
#include "RenderSystem.h"
#include "OBJLoader.h"
#include "Light.h"
#include "EmptyRenderer.h"
#include "InstanceRenderSystem.h"
#include "ParticleLoader.h"
#include "AnimatedMesh.h"
#include "ASDLoader.h"
#include "CustomInstanceRenderer.h"
#include "GuiRenderSystem.h"
#include "SAT.h"

int particles;
int entityh;
int animated;
int renderentities;
int guis;
SAT sat;
OBB obb1;
OBB obb2;
TestState::TestState()
{
	
}
void TestState::init()
{
	particles = ParticleLoader::loadParticle("particle", handler);
	camera.pointToLookAt = vec3(0);
	GameComponent g;
	g.a = 23;
	Mesh m(OBJLoader::loadOBJ("objs/cube.obj"));
	for (int i = 0; i < m.data.vertices.size(); i++) {
		std::cout << m.data.vertices[i] << ", ";
	}
	m.scale = vec3(1);
	m.position = vec3(1);
	m.texture = new Texture("res/red.png");
	Texture *green = new Texture("res/green.png");
	Transformation proba0;
	proba0.pos.x = 10;
	/*Mesh proba1(OBJLoader::loadOBJ("objs/cube.obj"));
	proba1.texture = green;
	int proba = handler.makeEntity(proba1,proba0);*/
	m.outLineColor = vec4(1);
	m.texture->bloomMap = green->texture_id;
	Transformation transform;
	transform.pos = vec3(0,0,0);
	transform.scale = vec3(1,1,1);
	entityh = handler.makeEntity(m, transform);
	Light l(glm::vec3(0, 1000, 5), glm::vec3(1), glm::vec3(1, 0, 0));
	Light light0(glm::vec3(0, 50, -50), glm::vec3(1, 0, 0), glm::vec3(1, 0.01f, 0.0001f));
	Light light2(glm::vec3(0, 50, 50), glm::vec3(0, 0, 1), glm::vec3(1, 0.01f, 0.0001f));

	int light = handler.makeEntity(l,light0,light2);
	EmptyRendererComponent er("shaders/default");
	int filters = handler.makeEntity(er,transform);
	//InstanceComponent icom(OBJLoader::loadOBJ("objs/cube.obj"));
	/*for (int i = -3; i < 3; i++) {
		for (int j = -3; j < 3; j++) {
			for (int g = -3; g < 3; g++) {
				icom.addInstance(vec3(i*3, j*3, g*3), vec3(), vec3(1), green);
			}
		}
	}*/
	//int instances = handler.makeEntity(icom);
	/*BillBoard b(new Texture("res/green.png"),vec3(),vec2(1),0);
	int billboards = handler.makeEntity(b);
	Texture *ant = new Texture("res/red.png");
	ant->bloomMap = ant->texture_id;
	*///ModelData skin = ASDLoader::loadSkin("animations/idle.asd");
	/*AnimatedMesh *anime = new AnimatedMesh(vec3(), &skin, ASDLoader::loadAnimation("animations/idle.asd"), vec3(10.f),ant);
	anime->rotation.z = 1.56;
	anime->rotation.x = -1.56;
	anime->transformation *= .1f;
	Animation a = ASDLoader::loadAnimation("animations/idle.asd");
	Transformation animt;
	animt.rotation.z = 1.56;
	animt.rotation.x = -1.56;
	animated = handler.makeEntity(*anime,animt);*/
	CustomInstanceRenderer *creer = new CustomInstanceRenderer();

	/*GUIComponent gui(green);
	
	
	guis = handler.makeEntity(gui);*/
}
int zuwe = 0;
void TestState::update()
{
	if (input->isKeyDown(keys::KEY_A)) {
		//action::translate(entityh, vec3(.1, 0, 0));
		if (action::getRotation(animated).z < 1.50) {
			action::rotate(animated, .2, vec3(0, 0, 1));
		}
		else if (action::getRotation(animated).z > 1.6) {
			action::rotate(animated, -.2, vec3(0, 0, 1));
		}
		action::translate(animated, vec3(1, 0, 0));

		zuwe++;
	}
	if (input->isKeyDown(keys::KEY_D)) {
		//action::translate(entityh, vec3(-.1, 0, 0));
		if (action::getRotation(animated).z < -1.7) {
			action::rotate(animated, .2, vec3(0, 0, 1));
		}
		else if (action::getRotation(animated).z > -1.4) {
			action::rotate(animated, -.2, vec3(0, 0, 1));
		}
		action::translate(animated, vec3(-1, 0, 0));

		zuwe++;
	}
	if (input->isKeyDown(keys::KEY_W)) {
		//action::translate(entityh, vec3(0, .1, 0));
		if (action::getRotation(animated).z < 0) {
			action::rotate(animated, .2, vec3(0, 0, 1));
		}
		else if (action::getRotation(animated).z > 0.2) {
			action::rotate(animated, -.2, vec3(0, 0, 1));
		}
		action::translate(animated, vec3(0, 0, 1));

		
		zuwe++;
	}
	if (input->isKeyDown(keys::KEY_S)) {
		//action::translate(entityh, vec3(0, -.1, 0));
		if (action::getRotation(animated).z < 3.0) {
			action::rotate(animated, .2, vec3(0, 0, 1));
		}
		else if (action::getRotation(animated).z > 3.2) {
			action::rotate(animated, -.2, vec3(0, 0, 1));
		}
		action::translate(animated, vec3(0, 0, -1));

		zuwe++;
	}
	//action::emit(particles);
	if (zuwe < 39) {
		action::setFrame(animated, zuwe);
	}
	else {
		zuwe = 0;
	}

	
	camera.anglex -= input->getMouseXf(keys::MOUSE_BUTTON_LEFT) / 10;
	camera.angley -= input->getMouseYf(keys::MOUSE_BUTTON_LEFT) / 10;
	camera.distance += input->scroll * 10;
	input->scroll = 0;
}
void TestState::render()
{
	cout << "renderin.." << endl;
}
TestState::~TestState()
{
}
