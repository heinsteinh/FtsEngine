#pragma once


#include "GameObject.h"
#include "Component.h"

namespace framework
{
	namespace comp
	{

		class PositionComponent : public Component
		{

		public:		

			PositionComponent(GameObjectPtr pOwner);
			PositionComponent(GameObjectPtr pOwner, const vec3& initial_pos);
			virtual ~PositionComponent();

			vec3 _pos;
		};

	}
}
