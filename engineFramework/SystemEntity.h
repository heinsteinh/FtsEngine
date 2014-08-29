#pragma once

#include <unordered_map>

#include "Entity.h"
#include "NonCopyable.h"
#include "System.h"

namespace entityx {


	class SystemManager;


	/**
	* Base System class. Generally should not be directly used, instead see System<Derived>.
	*/
	class BaseSystem : entityx::help::NonCopyable {
	public:
		typedef uint64_t Family;

		virtual ~BaseSystem() {}

		/**
		* Called once all Systems have been added to the SystemManager.
		*
		* Typically used to set up event handlers.
		*/
		virtual void configure(core::EventChannel &events) {}

		/**
		* Apply System behavior.
		*
		* Called every game step.
		*/
		virtual void update(EntityManager &entities, core::EventChannel &events, double dt) = 0;


		virtual bool init(){ return true; }
		virtual void destroy(){}

		static Family family_counter_;

	protected:
	};


	/**
	* Use this class when implementing Systems.
	*
	* struct MovementSystem : public System<MovementSystem> {
	* void update(EntityManager &entities, EventManager &events, double dt) {
	* // Do stuff to/with entities...
	* }
	* }
	*/
	template <typename Derived>
	class System : public BaseSystem 
	{
	public:
		virtual ~System() {}

	private:
		friend class SystemManager;

		static Family family() 
		{
			static Family family = family_counter_++;
			return family;
		}

		
	};


	//https://github.com/alecthomas/entityx/blob/master/entityx/System.h
	class SystemManager  : public core::System 
	{
	public:
		SystemManager();
		
		
		/* general */
		bool init();

		void update();
	
		void shutdown();
	


		/**
		* Add a System to the SystemManager.
		*
		* Must be called before Systems can be used.
		*
		* eg.
		* std::shared_ptr<MovementSystem> movement = entityx::make_shared<MovementSystem>();
		* system.add(movement);
		*/
		template <typename S>
		void add(std::shared_ptr<S> system) 
		{
			systems_.insert(std::make_pair(S::family(), system));
		}

		/**
		* Add a System to the SystemManager.
		*
		* Must be called before Systems can be used.
		*
		* eg.
		* auto movement = system.add<MovementSystem>();
		*/
		template <typename S, typename ... Args>
		std::shared_ptr<S> add(Args && ... args) 
		{
			std::shared_ptr<S> s(new S(std::forward<Args>(args) ...));
			add(s);
			return s;
		}

		/**
		* Retrieve the registered System instance, if any.
		*
		* std::shared_ptr<CollisionSystem> collisions = systems.system<CollisionSystem>();
		*
		* @return System instance or empty shared_std::shared_ptr<S>.
		*/
		template <typename S>
		std::shared_ptr<S> system()
		{
			auto it = systems_.find(S::family());
			
			assert(it != systems_.end());

			return it == systems_.end() ? std::shared_ptr<S>() : std::shared_ptr<S>(std::static_pointer_cast<S>(it->second));
		}

		/**
		* Call the System::update() method for a registered system.
		*/
		template <typename S>
		void update(double dt) 
		{
			assert(initialized_ && "SystemManager::configure() not called");
			std::shared_ptr<S> s = system<S>();
			
			core::EventChannel event_manager_;
			s->update(mEngine->getEntityManager(), event_manager_, dt);

		}

		/**
		* Configure the system. Call after adding all Systems.
		*
		* This is typically used to set up event handlers.
		*/
		void configure();

	private:
		bool initialized_ = false;
		
		//std::unordered_map<BaseSystem::Family, std::shared_ptr<BaseSystem>> systems_;
		typedef std::unordered_map<BaseSystem::Family, std::shared_ptr<BaseSystem>> systems;
		systems systems_;
	};

} // namespace entityx