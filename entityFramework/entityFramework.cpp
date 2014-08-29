// entityFramework.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"


#include "PositionComponent.h"
#include "VelocityComponent.h"
#include "DisplayComponent.h"

#include "MoveSystem.h"
#include "RenderSystem.h"

#include "Entity.h"
#include "Engine.h"



using namespace std;

#pragma mark
#pragma mark Main
int _tmain(int argc, _TCHAR* argv[])
{

	Entity* player = new Entity();


	PositionComponent* pos = new PositionComponent(0, 0, 0);
	VelocityComponent* vel = new VelocityComponent(0.1, 0.1, 0);

	DisplayObject view = { 0, 0, 90 };
	DisplayComponent* dis = new DisplayComponent(view);

	player->add(pos);
	player->add(vel);
	player->add(dis);

	Engine* engine = new Engine();
	{

		MoveSystem* mover = new MoveSystem();
		{
			MoveNode* moveN = new MoveNode{ pos, vel };
			mover->addItem(moveN);
		}

		RenderSystem* renderer = new RenderSystem();
		{
			RenderNode* rendN = new RenderNode{ dis, pos };
			renderer->addItem(rendN);
		}

		engine->addEntity(player);
		engine->addSystem(mover, 1);
		engine->addSystem(renderer, 2);
	}

	float dt = 0.017f;
	std::cout << "\n\nDO STUFF!\n";
	std::cout << "Hello, World!\n";
	std::cout << "DO STUFF!\n\n\n";


	engine->update(1 / 60);

	delete engine;

	return 0;
}



/*

#include "micro_ecs.h"

#include <iostream>
using std::cout;
using std::endl;


namespace ECS
{


class PositionComponent : public Component {
public:
int x, y;
PositionComponent(int x, int y) : x(x), y(y) {}
};

class VelocityComponent : public Component {
public:
int vx, vy;
VelocityComponent(int vx, int vy) : vx(vx), vy(vy) {}
};

class VelocitySystem : public System<PositionComponent, VelocityComponent> {
public:
VelocitySystem() {}

void logic(Entity& e) {
auto pos = e.GetComponent<PositionComponent>();
auto vel = e.GetComponent<VelocityComponent>();
pos->x += vel->vx;
pos->y += vel->vy;
}
};

void printPosVel(Entity& e)
{
auto pos = e.GetComponent<PositionComponent>();
auto vel = e.GetComponent<VelocityComponent>();
cout << "pos: " << pos->x << ", " << pos->y << " ";
cout << "vel: " << vel->vx << ", " << vel->vy << endl;
}

}

int _tmain(int argc, _TCHAR* argv[])
{
	//VelocitySystem s;

	//Entity e;
	//e.AddComponent(new PositionComponent(32, 64));
	//e.AddComponent<VelocityComponent>(1, 2);

	//printPosVel(e);
	//s.process(e);
	//printPosVel(e);


}*/
