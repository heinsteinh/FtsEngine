#include "stdafx.h"
#include "Entity.h"



namespace entityx 
{

	const Entity::Id Entity::INVALID;
	BaseComponent::Family BaseComponent::family_counter_ = 0;

	void Entity::invalidate() {
		id_ = INVALID;
		manager_ = nullptr;
	}

	void Entity::destroy() 
	{
		assert(valid());
		manager_->destroy(id_);
		invalidate();
	}

	std::bitset<entityx::MAX_COMPONENTS> Entity::component_mask() const 
	{
		return manager_->component_mask(id_);
	}

	EntityManager::EntityManager()  
	{
		
		core::EventChannel event_manager_;
		event_manager_.add<EntityCreatedEvent>(*this);
		event_manager_.add<EntityDestroyedEvent>(*this);
	}

	EntityManager::~EntityManager() 
	{
		reset();
		core::EventChannel event_manager_;
		event_manager_.remove<EntityCreatedEvent>(*this);
		event_manager_.remove<EntityDestroyedEvent>(*this);
	}




	void EntityManager::reset() {
		for (BasePool *pool : component_pools_) {
			if (pool) delete pool;
		}
		component_pools_.clear();
		entity_component_mask_.clear();
		entity_version_.clear();
		free_list_.clear();
		index_counter_ = 0;
	}


} // namespace entityx