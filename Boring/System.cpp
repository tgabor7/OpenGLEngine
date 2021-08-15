#include "System.h"



System::System()
{
}

System::~System()
{
}
void System::addComponentType(int type)
{
	types.push_back(type);
}
void System::update(double delta)
{
	for (int i = 0; i < EntityHandler::entities.size(); i++) {
		components = EntityHandler::entities[i].second;
		bool b = false;
		bool g = true;
		for (int i = 0; i < types.size(); i++) {
			b = false;
			for (int j = 0; j < components.size(); j++) {
				if (types[i] == components[j].second) {
					b = true;
				}
			}
			if (!b) g = false;
		}
		if(g) updateComponents(delta);
	}
	updateSystem(delta);
}
void SystemList::addSystem(System *system)
{
	this->systems.push_back(system);
}
void SystemList::update(double d)
{
	for (int i = 0; i < this->systems.size(); i++) {
		systems[i]->update(d);
	}
}