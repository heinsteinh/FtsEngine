
#pragma once

#include <iostream>

enum SubSystemType
{
	MOVE = 1 << 0,
	RENDER = 1 << 1
};

class ISystem {
public:
	ISystem(){ std::cout << "\t! ISystem, constructor!\n"; }
	ISystem(SubSystemType t) : type(t){ std::cout << "\t! ISystem, new of type (" << this->type << ")\n"; }
	virtual ~ISystem(){ std::cout << "| X ISystem, destructor of type (" << this->type << ")\n"; }

	virtual void start() = 0;
	virtual void update(float time) = 0;
	virtual void end() = 0;

	SubSystemType type;
};
