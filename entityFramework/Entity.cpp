#include "stdafx.h"
#include "Entity.h"



int Entity::sEntityID = 0;

Entity::Entity(){
	this->mID = sEntityID;
	sEntityID++;
	std::cout << "! Entity, new with ID (" << mID << ")!\n";
}

Entity::~Entity(){
	cleanup();
}

void Entity::cleanup(){

	if (!components.empty()){
		std::cout << "| X Entity:(" << this->mID << ") containts (" << components.size() << ") components\n";
		for (std::map<int, IComponent*>::iterator it = components.begin(); it != components.end(); ++it) {
			delete it->second;
			it->second = NULL;
		}
		components.clear();
	}
}

void Entity::add(IComponent *component){
	std::cout << "+ Entity, component of type (" << component->type << ") was added!\n";

	components.insert(std::pair<int, IComponent*>(component->type, component));
}

void Entity::remove(int component){
	components.erase(component);
}

IComponent* Entity::get(int component){
	return components[component];
}