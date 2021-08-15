#include "SAT.h"
#include "Transformation.h"
#include "Maths.h"

SAT::SAT()
{
	addComponentType(Transformation::type);
	addComponentType(OBB::type);
}
bool SAT::collide(int a, int b)
{
	OBB* o = (OBB*)EntityHandler::getComponent(a, OBB::type);
	OBB* o0 = (OBB*)EntityHandler::getComponent(b, OBB::type);

	vector<vec3> avertices = o->vertices;
	vector<vec3> bvertices = o0->vertices;

	vec3 aedge0 = avertices[0] - avertices[1];
	vec3 aedge1 = avertices[0] - avertices[2];
	vec3 aedge2 = avertices[0] - avertices[4];

	vec3 bedge0 = bvertices[0] - bvertices[1];
	vec3 bedge1 = bvertices[0] - bvertices[2];
	vec3 bedge2 = bvertices[0] - bvertices[4];

	vector<vec3> axises;

	axises.push_back(cross(aedge0, bedge0));
	axises.push_back(cross(aedge0, bedge1));
	axises.push_back(cross(aedge0, bedge2));
	axises.push_back(cross(aedge1, bedge0));
	axises.push_back(cross(aedge1, bedge1));
	axises.push_back(cross(aedge1, bedge2));
	axises.push_back(cross(aedge2, bedge0));
	axises.push_back(cross(aedge2, bedge1));
	axises.push_back(cross(aedge2, bedge2));
	
	axises.push_back(cross(aedge0, aedge1));
	axises.push_back(cross(aedge0, aedge2));
	axises.push_back(cross(aedge1, aedge2));
	
	axises.push_back(cross(bedge0, bedge1));
	axises.push_back(cross(bedge0, bedge2));
	axises.push_back(cross(bedge1, bedge2));



	vector<vector<float>> amins;
	vector<vector<float>> bmins;

	bool collides = true;

	for (int i = 0; i < axises.size(); i++) {

		axises[i] = normalize(axises[i]);

		amins.push_back(createDots(axises[i], avertices));
		bmins.push_back(createDots(axises[i], bvertices));

		float amin = getMin(amins[i]);
		float amax = getMax(amins[i]);

		float bmin = getMin(bmins[i]);
		float bmax = getMax(bmins[i]);

		if (bmin >= amax || bmax <= amin) {
			collides = false;
		}
	}



	return collides;
}
vector<float> SAT::createDots(vec3 axis, vector<vec3> vertices)
{
	vector<float> result;
	for (int i = 0; i < vertices.size(); i++) {
		result.push_back(dot(axis, vertices[i]));
	}
	return result;
}
float SAT::getMin(vector<float> data)
{
	float result = data[0];
	for (int i = 0; i < data.size(); i++) {
		if (data[i] < result) {
			result = data[i];
		}
	}
	return result;
}
float SAT::getMax(vector<float> data)
{
	float result = data[0];
	for (int i = 0; i < data.size(); i++) {
		if (data[i] > result) {
			result = data[i];
		}
	}
	return result;
}
void SAT::updateComponents(double delta)
{
	Transformation* t = (Transformation*)getComponent(Transformation::type)[0];
	OBB *o = (OBB*)getComponent(OBB::type)[0];
	for(int i = 0;i<o->vertices.size();i++){
		
		mat4x4 transform = functions::createTransformationMatrix(t->pos, t->rotation, t->scale);

		vec4 v = vec4(o->data[i].x, o->data[i].y, o->data[i].z,1.0f);

		v = transform * v;

		o->vertices[i] = vec3(v.x, v.y, v.z);
	}
	o->position = t->pos;
	o->rotation = t->rotation;
	o->scale = t->scale;
}
void SAT::updateSystem(double delta)
{

}
SAT::~SAT()
{
}
