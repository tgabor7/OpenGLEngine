#pragma once
#include <vector>
#include <string>
#include <typeinfo>
#include <iostream>

class BaseComponent
{
public:
	
	BaseComponent() {
	
	}
	static int id;
	static int create() {
		return id++;
	}
	
private:
	
};
class Entity
{
public:
	static int id;
};
template<class T>
class Component : public BaseComponent
{
public:
	Component() {
		/*type = 0;
		std::string name = typeid(this).name();
		bool incremet = true;
		int size = EntityHandler::components.size();
		for (int i = 0; i < size; i++) {
			if (name == EntityHandler::components[i].second) {
				incremet = false;
				type = i;
			}
		}
		if (incremet) {
			type = size;
			EntityHandler::components.push_back({type,name});
		}*/
	}
	//static int type;
	static const int type;

	~Component(){}
};
template<class T>
const int Component<T>::type(BaseComponent::create());
//template<class T>
//int Component<T>::type = 0;

class EntityHandler
{
public:
	EntityHandler();
	/*static int makeEntitiy(std::vector<BaseComponent*> a) {
		int ID = Entity::id++;
		std::vector<std::pair<char*,int>> comps;
		for (int i = 0; i < a.size(); i++) {
			comps.push_back({ (char*)a[i] ,a[i]->type});
		}
		entities.push_back({ID,comps});
		return ID;
	}*/
	template<class T>
	int makeEntity(T &a)
	{
		int ID = Entity::id++;
		std::vector<std::pair<BaseComponent*, int>> comps;
		T *com = new T(a);
		comps.push_back({ com ,T::type });
		entities.push_back({ ID,comps });
		return ID;
	}
	template<class A,class B>
	int makeEntity(A &a,B &b)
	{
		int ID = Entity::id++;
		std::vector<std::pair<BaseComponent*, int>> comps;
		A *coma = new A(a);
		B *comb = new B(b);
		comps.push_back({ coma ,A::type });
		comps.push_back({ comb ,B::type });
		entities.push_back({ ID,comps });
		return ID;
	}
	template<class A, class B,class C>
	int makeEntity(A &a, B &b,C &c)
	{
		int ID = Entity::id++;
		std::vector<std::pair<BaseComponent*, int>> comps;
		A *coma = new A(a);
		B *comb = new B(b);
		C *comc = new C(c);
		comps.push_back({ coma ,A::type });
		comps.push_back({comb ,B::type });
		comps.push_back({ comc ,C::type });
		entities.push_back({ ID,comps });
		return ID;
	}
	template<class A, class B, class C,class D>
	int makeEntity(A &a, B &b, C &c,D &d)
	{
		int ID = Entity::id++;
		std::vector<std::pair<BaseComponent*, int>> comps;
		A *coma = new A(a);
		B *comb = new B(b);
		C *comc = new C(c);
		D *comd = new D(d);
		comps.push_back({ coma ,A::type });
		comps.push_back({ comb ,B::type });
		comps.push_back({ comc ,C::type });
		comps.push_back({ comd ,D::type });
		entities.push_back({ ID,comps });
		return ID;
	}
	template<class A, class B, class C, class D,class F>
	int makeEntity(A &a, B &b, C &c, D &d,F &f)
	{
		int ID = Entity::id++;
		std::vector<std::pair<BaseComponent*, int>> comps;
		A *coma = new A(a);
		B *comb = new B(b);
		C *comc = new C(c);
		D *comd = new D(d);
		F *comf = new F(f);
		comps.push_back({ coma ,A::type });
		comps.push_back({ comb ,B::type });
		comps.push_back({ comc ,C::type });
		comps.push_back({ comd ,D::type });
		comps.push_back({ comf ,F::type });
		entities.push_back({ ID,comps });
		return ID;
	}
	static BaseComponent* getComponent(int entityHandle,int type) {
		for (int i = 0; i < entities.size(); i++) {
			if (entities[i].first == entityHandle) {
				for (int j = 0; j < entities[i].second.size(); j++) {
					if (type == entities[i].second[j].second) {
						return entities[i].second[j].first;
					}
				}
			}
		}
		return nullptr;
	}
	bool deleteEntity(int id);
	static std::vector < std::pair<int, std::vector<std::pair<BaseComponent*,int>>> > entities;
	//static std::vector < std::pair<int, std::string>> components;
	~EntityHandler();
};

class TestComponent : public Component<TestComponent>
{
public:
	TestComponent(){}
	float x = 0;
	float y = 0;
	~TestComponent() {}
};

class GameComponent : public Component<GameComponent>
{
public:
	GameComponent() {}
	int a = 42;
	~GameComponent() {}
};

