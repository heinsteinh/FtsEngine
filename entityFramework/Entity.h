#pragma once



#include "IComponent.h"
#include <map>

class Entity 
{
	static int sEntityID;

public:
	Entity();
	~Entity();
	void cleanup();
	void add(IComponent *component);
	void remove(int component);
	IComponent* get(int component);
	int mID;

private:
	std::map<int, IComponent*> components;
	Entity* previous;
	Entity* next;


};

