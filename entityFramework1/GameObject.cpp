#include "stdafx.h"
#include "GameObject.h"



namespace famework
{
	namespace comp
	{

		GameObject::GameObject(const std::string& name)
		{
			std::cout << "Ctor GameObject: " << name.c_str() << std::endl;
		}


		GameObject::GameObject(void)
		{
			std::cout << "Ctor GameObject" << std::endl;
		}


		GameObject::~GameObject(void)
		{
			std::cout << "Dtor GameObject" << std::endl;
		}

		Component* GameObject::GetComponent(unsigned int id)
		{
			ComponentUnorderedMapIterator result = m_components.find(id);
			return result == m_components.end() ? NULL: result->second;
		}

	}
}
