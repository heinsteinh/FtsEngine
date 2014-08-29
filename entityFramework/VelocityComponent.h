#pragma once

#include "IComponent.h"

class VelocityComponent : public IComponent{
public:
	VelocityComponent(){}
	VelocityComponent(float velocityX, float velocityY, float angularVelocity) :IComponent(VELOCITY){
		//std::cout << "! VelocityComponent, constructor!\n";

		this->type = VELOCITY;
		this->velocityX = velocityX;
		this->velocityY = velocityY;
		this->angularVelocity = angularVelocity;
	}
	~VelocityComponent(){
		//std::cout << "X VelocityComponent, destructor!\n";
	}

	float velocityX;
	float velocityY;
	float angularVelocity;
};

