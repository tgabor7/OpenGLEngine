#include "PhysicsTest.h"
#include "Mesh.h"
#include "OBJLoader.h"
#include "Transformation.h"
#include "SAT.h"
#include "Light.h"
#include "EmptyRenderer.h"

OBB boundingBox1;
OBB boundingbox;

int box_0;
int box_1;
PhysicsTest::PhysicsTest()
{

}
void PhysicsTest::init()
{
	Mesh m(OBJLoader::loadOBJ("objs/cube.obj"));
	m.scale = vec3(1);
	m.position = vec3(1);
	Texture *texture = new Texture("res/green.png");
	m.texture = new Texture("res/red.png");
	m.texture->bloomMap = texture->texture_id;
	Transformation t;
	boundingbox = OBB(vec3(),vec3(1));
	box_0 = handler.makeEntity(m, boundingbox,t);
	
	Mesh m1(OBJLoader::loadOBJ("objs/cube.obj"));
	m1.texture = new Texture("res/green.png");

	Transformation t1;
	boundingBox1 = OBB(vec3(1), vec3(1));

	t1.pos = vec3(10, 10, 0);
	t1.scale = vec3(3,1,1);
	box_1 = handler.makeEntity(m1,t1,boundingBox1);

	Light l(glm::vec3(0, 1000, -1000), glm::vec3(1), glm::vec3(1, 0, 0));
	Light light0(glm::vec3(50, 1000, -50), glm::vec3(1), glm::vec3(1, 0.01f, 0.0001f));
	Light light2(glm::vec3(1000, 1000, 50), glm::vec3(1), glm::vec3(1, 0.01f, 0.0001f));

	int light = handler.makeEntity(l, light0, light2);

	EmptyRendererComponent erc("shaders/crt");

	int post = handler.makeEntity(erc);
}
void PhysicsTest::update()
{
	camera.anglex -= input->getMouseXf(keys::MOUSE_BUTTON_LEFT) / 10;
	camera.angley -= input->getMouseYf(keys::MOUSE_BUTTON_LEFT) / 10;
	camera.distance += input->scroll * 10;
	input->scroll = 0;

	if (input->isKeyDown(keys::KEY_A)) {
		action::translate(box_1, vec3(.1, 0, 0));
	}
	if (input->isKeyDown(keys::KEY_D)) {
		action::translate(box_1, vec3(-.1, 0, 0));
	}
	if (input->isKeyDown(keys::KEY_W)) {
		action::translate(box_1, vec3(0, .1f, 0));
	}
	if (input->isKeyDown(keys::KEY_S)) {
		action::translate(box_1, vec3(0, -.1f, 0));
	}
	if (input->isKeyDown(keys::KEY_R)) {
		action::rotate(box_1, .1f, vec3(0, 0, 1));
	}
	//cout << SAT::collide(box_0, box_1) << "\n";
	
}
void PhysicsTest::render()
{
	cout << "renderin.." << endl;
}
PhysicsTest::~PhysicsTest()
{
}
