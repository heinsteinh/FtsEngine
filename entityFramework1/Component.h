
#pragma once


#include <memory>
#include <unordered_map>
#include <string>

typedef unsigned long int component_id;
typedef unsigned long int component_type_id;

typedef struct
{
	float x;
	float y;
} vec2;


typedef struct
{
	float x;
	float y;
	float z;
} vec3;



namespace framework
{
	namespace comp
	{
		class GameObject;
		typedef std::shared_ptr<GameObject> GameObjectPtr;
		class Component
		{
		public:
			typedef std::shared_ptr<Component> ComponentPtr;

		public:
			explicit Component(GameObjectPtr pOwner): m_pOwner(pOwner), m_id_(getNewTypeID())
			{
			}

			virtual ~Component() {}
			virtual void Initialize() = 0;


			unsigned int GetId() { return this->m_id_; }
			GameObjectPtr GetOwner() { return m_pOwner; }


		protected:
			component_id m_id_;
			static component_type_id getNewTypeID();			


		private:
			// the shift value of the next class id to be created
			static int nextTypeId_;
			GameObjectPtr  m_pOwner;
		};

	}
}