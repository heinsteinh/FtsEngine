
#pragma once

#include "ISystem.h"
#include <vector>

struct RenderNode 
{
	DisplayComponent* display;
	PositionComponent* position;
};

class RenderSystem : public ISystem {
public:
	RenderSystem() :ISystem(RENDER){ /*std::cout << "! RenderSystem, constructor!\n";*/ }
	~RenderSystem(){ /*std::cout << "X RenderSystem, destructor!\n";*/ }

	void start(){ std::cout << "? RenderSystem, start!\n"; }
	void end(){ std::cout << "? RenderSystem, update!\n"; }

	void addItem(RenderNode* node){ targets.push_back(node); }

	void update(float time){
		std::cout << "& RenderSystem, update!\n";
		for (std::vector<RenderNode*>::iterator it = targets.begin(); it != targets.end(); ++it) {
			RenderNode* target = *it;
			std::cout << "&--& RenderSystem, RenderNode:" << target->position->x << "!\n";

			target->display->view.x = target->position->x;
			target->display->view.y = target->position->y;
			target->display->view.rotation = target->position->rotation;
		}
	}

private:
	std::vector<RenderNode*> targets;
};