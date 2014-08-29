
#pragma once


#include <iostream>

enum SubComponentType
{
	POSITION = 1 << 0,
	VELOCITY = 1 << 1,
	DISPLAY = 1 << 2
};

class IComponent {
public:
	IComponent(){ std::cout << "\t! IComponent, constructor (--)\n"; }
	IComponent(SubComponentType t) : type(t){ std::cout << "\t! IComponent, new of type (" << this->type << ")\n"; }
	virtual ~IComponent(){ std::cout << "| | X IComponent, destructor of type (" << this->type << ")\n"; }

	SubComponentType type;
};