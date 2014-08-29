#include "stdafx.h"
#include "PositionComponent.h"



namespace framework
{
	namespace comp
	{

		
		PositionComponent::PositionComponent(GameObjectPtr pOwner) :Component(pOwner)
		{
			 this->getNewTypeID();
			_pos.x = 0;
			_pos.y = 0;
			_pos.z = 0;
		}


		PositionComponent::PositionComponent(GameObjectPtr pOwner, const vec3& initial_pos) :Component(pOwner)
		{
			_pos = initial_pos;
		}



		PositionComponent::~PositionComponent(void)
		{
		}

	}
}