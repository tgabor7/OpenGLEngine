#include "EntityHandler.h"

int BaseComponent::id = 0;
//int BaseComponent::type = 0;
int Entity::id = 0;
std::vector < std::pair<int, std::vector<std::pair<BaseComponent*, int>>> > EntityHandler::entities;
//std::vector < std::pair<int, std::string>> EntityHandler::components;

EntityHandler::EntityHandler()
{
}
bool EntityHandler::deleteEntity(int id)
{
	bool result;
	for (int i = 0; i < entities.size(); i++) {
		if (entities[i].first == id) {
			for (int j = 0; j < entities[i].second.size(); j++) {
				delete entities[i].second[j].first;
				entities[i].second[j].first = nullptr;
			}
			entities[i].second.clear();
			entities.erase(entities.begin() + i);
			
			result = true;
		}
	}
	return result;
}

EntityHandler::~EntityHandler()
{
	for (int i = 0; i < entities.size(); i++) {
		for (int j = 0; j < entities[i].second.size(); j++) {
			delete entities[i].second[j].first;
			entities[i].second[j].first = nullptr;
		}
		entities[i].second.clear();
	}
	entities.clear();
}
