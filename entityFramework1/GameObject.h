#pragma once

#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <iostream>

namespace famework
{
	namespace comp
	{

		class Component;				
		class GameObject  //: public std::enable_shared_from_this<GameObject>
		{

		public:
			typedef std::shared_ptr<GameObject> GameObjectPtr;

			template <class T>
			friend T* component_cast(GameObject& object);
			template <class T>
			friend T* component_cast(GameObject* pObject);
			template <class T>
			friend T* component_cast(GameObjectPtr pObject);


		private:
			typedef std::tr1::unordered_map<unsigned int, Component*> ComponentUnorderedMap;
			typedef ComponentUnorderedMap::iterator ComponentUnorderedMapIterator;
			ComponentUnorderedMap m_components;


			template <class T>
			T* GetComponent() { return static_cast<T*>(GetComponent(T::GetId())); }
			Component* GetComponent(unsigned int id);
			

		public:
			GameObject(const std::string& name);
			GameObject();

			virtual ~GameObject(void);


			template <class T>
			bool AddComponent();



		};



		template <class T>
		T* component_cast(GameObject& object)
		{
			return object.GetComponent<T>();
		}


		template <class T>
		T* component_cast(GameObject* pObject)
		{
			T* pComponent = NULL;
			if (pObject)
			{
				pComponent = pObject->GetComponent<T>();
			}
			return pComponent;
		}

		template <class T>
		T* component_cast(GameObject::GameObjectPtr pObject)
		{
			T* pComponent = NULL;
			if (pObject)
			{
				pComponent = pObject->GetComponent<T>();
			}
			return pComponent;
		}


		template <class T>
		bool GameObject::AddComponent()
		{
			bool added = false;
			ComponentUnorderedMapIterator result = m_components.find(T::GetId());
			if (result == m_components.end())
			{
				T* pNewComponent = new T(this);
				if (pNewComponent)
				{
					std::pair<unsigned int, Component*> newComponent(T::GetId(), pNewComponent);
					std::pair< ComponentUnorderedMapIterator, bool> addedIter = m_components.insert(newComponent);
					added = addedIter.second;
				}
			}
			return added;
		}

		typedef std::shared_ptr<GameObject> GameObjectPtr;
	}
}