
#pragma once

#include "ISystem.h"
#include <vector>

struct MoveNode 
{
	PositionComponent* position;
	VelocityComponent* velocity;
};

class MoveSystem : public ISystem {
public:
	MoveSystem() :ISystem(MOVE){ /*std::cout << "! MoveSystem, constructor!\n";*/ }
	~MoveSystem(){ /*std::cout << "X MoveSystem, destructor!\n";*/ }

	void start(){ std::cout << "? MoveSystem, start!\n"; }
	void end(){ std::cout << "? MoveSystem, update!\n"; }

	void addItem(MoveNode* node){ targets.push_back(node); }

	void update(float time){
		std::cout << "& MoveSystem, update!\n";

		for (std::vector<MoveNode*>::iterator it = targets.begin(); it != targets.end(); ++it) {
			MoveNode* target = *it;
			std::cout << "&--& MoveSystem, MoveNode: " << target->position->x << "!\n";

			target->position->x += target->velocity->velocityX;
			target->position->y += target->velocity->velocityY;
			target->position->rotation += target->velocity->angularVelocity;
		}
	}

private:
	std::vector<MoveNode*> targets;
};