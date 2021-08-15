#pragma once
#include "EntityHandler.h"

class System
{
public:
	System();
	virtual void updateSystem(double delta) {};
	virtual void updateComponents(double delta) {};
	void update(double delta);
	void addComponentType(int type);
	template<class T>
	std::vector<T> getComponents() {
		std::vector<T> result;
		for (int i = 0; i < EntityHandler::entities.size(); i++) {
			for (int j = 0; j < EntityHandler::entities[i].second.size(); j++) {
				if (EntityHandler::entities[i].second[j].second == T::type) {
					result.push_back(*(T*)EntityHandler::entities[i].second[j].first);
				}
			}
		}
		return result;
	}
	std::vector<BaseComponent*> getComponent(int type)
	{
		std::vector<BaseComponent*> result;
		for(int i = 0;i<components.size();i++){
			if (components[i].second == type) {
				result.push_back(components[i].first);
			}
		}
		return result;
	}
	std::vector<BaseComponent*> getComponents(int type)
	{
		std::vector<BaseComponent*> result;
		for (int i = 0; i < EntityHandler::entities.size(); i++) {
			for (int j = 0; j < EntityHandler::entities[i].second.size(); j++) {
				if (EntityHandler::entities[i].second[j].second == type) {
					result.push_back(EntityHandler::entities[i].second[j].first);
				}
			}
		}
		return result;
	}
	std::vector<std::pair<BaseComponent*,int>> components;
	std::vector<int> types;
	~System();
};
class SystemList
{
public:
	void addSystem(System *system);
	void update(double d);
private:
	std::vector<System*> systems;
};
