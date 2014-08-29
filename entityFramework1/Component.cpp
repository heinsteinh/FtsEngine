
#include "stdafx.h"
#include "Component.h"


namespace framework
{

	namespace comp
	{
		int Component::nextTypeId_ = 0;

		component_type_id Component::getNewTypeID(void)
		{
			// returns 2 to the power of nextId_
			// then increments nextId_
			return 1 << nextTypeId_++;
		}
	}
}
