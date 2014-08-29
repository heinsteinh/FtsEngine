
#pragma once

#include "IComponent.h"

class PositionComponent : public IComponent{
public:
	PositionComponent(){}
	PositionComponent(float x, float y, float rotation) :IComponent(POSITION){
		//std::cout << "! PositionComponent, constructor!\n";

		this->type = POSITION;
		this->x = x;
		this->y = y;
		this->rotation = rotation;
	}
	~PositionComponent(){
		//std::cout << "X PositionComponent, destructor!\n";
	}

	float x;
	float y;
	float rotation;
};