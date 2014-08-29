#pragma once

#include "IComponent.h"

struct DisplayObject {
	float x;
	float y;
	float rotation;
};

class DisplayComponent : public IComponent{
public:
	DisplayComponent(){}
	DisplayComponent(DisplayObject view) :IComponent(DISPLAY){
		//std::cout << "! DisplayComponent, constructor!\n";

		this->type = DISPLAY;
		this->view = view;
	}
	~DisplayComponent()
	{
		//std::cout << "X DisplayComponent, destructor!\n";
	}

	DisplayObject view;
};

