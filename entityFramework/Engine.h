#pragma once


#include <iostream>
#include <vector>

class Entity;
class ISystem;

class Engine{
public:
	Engine();
	~Engine();

	void addEntity(Entity* entity);
	void removeEntity(Entity entity);

	void addSystem(ISystem *system, int priority);
	void removeSystem(ISystem* system);

	void update(float time);

private:

	void cleanup();

	std::vector<Entity*> entities;
	std::vector<ISystem*> systems;
};