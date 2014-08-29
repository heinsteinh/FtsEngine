#include "stdafx.h"
#include "Engine.h"


#include "Entity.h"
#include "ISystem.h"

Engine::Engine(){
	std::cout << "! Engine, constructor!\n";
}

Engine::~Engine(){
	cleanup();
	std::cout << "X Engine, destructor!\n";
}

void Engine::cleanup(){
	if (!entities.empty()){
		std::cout << "X Engine containts (" << entities.size() << ") entities\n";

		for (std::vector<Entity*>::iterator it = entities.begin(); it != entities.end(); ++it) {
			delete *it;
		}
		entities.clear();
	}
	if (!systems.empty()){
		std::cout << "X Engine containts (" << systems.size() << ") systems\n";

		for (std::vector<ISystem*>::iterator it = systems.begin(); it != systems.end(); ++it) {
			delete *it;
		}
		systems.clear();
	}

}

void Engine::addEntity(Entity* entity){
	std::cout << "+ Engine, Entity with id (" << entity->mID << ") was added\n";


	entities.push_back(entity);
}

void Engine::removeEntity(Entity entity){
	//entities.erase(std::remove(entities.begin(), entities.end(), entity), entities.end());
}

void Engine::addSystem(ISystem *system, int priority){
	std::cout << "+ Engine, System of type (" << system->type << ") was added\n";

	systems.push_back(system);
	// system->start();
}

void Engine::removeSystem(ISystem* system){
	system->end();
	//systems.erase(std::remove(systems.begin(), systems.end(), system), systems.end());
}

void Engine::update(float time){
	for (std::vector<ISystem*>::iterator it = systems.begin(); it != systems.end(); ++it) {
		ISystem *system = *it;
		system->update(time);
	}
}