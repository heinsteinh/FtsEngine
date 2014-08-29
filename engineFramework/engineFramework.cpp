// engineFramework.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"


#include <iostream>
#include <iostream>
#include <future>
#include <thread>
#include <string>


#include "SimpleGameState.h"
#include "StateMachineTest.h"

#include "eventbridge.h"
#include "eventhandler.h"
#include "eventchannel.h"

#include "PoolObject.h"
#include "Entity.h"

#include "task.h"
#include "taskmanager.h"

#include "SystemEntity.h"
#include "System.h"
#include "Engine.h"


#include "VideoSystem.h"
#include "Application.h"
#include "OpenGLESWindow.h"
#include "WindowEGL.h"

#include "Application_TestShaders.h"



#include <time.h>       /* time */
#include <stdlib.h>     /* srand, rand */




namespace test
{
	
	class TestSystem : public core::System
	{

	public:
		typedef std::shared_ptr<test::TestSystem> Ptr;
		typedef std::vector<input::TouchEvent> TouchSet;

		struct KeyUpEvent
		{
			KeyUpEvent(unsigned int key)
			: mKey(key)
			{ }

			const unsigned int mKey;
		};

		struct PreUpdate{};

	public:
		TestSystem() :System("TestSystem")
		{
			enableUpdater();
			mSomeConfigSetting = 10;
			addSetting("SomeConfigSetting", &mSomeConfigSetting);			
		}
		
		virtual ~TestSystem(){}
		virtual bool init(){  return true; }

		

		virtual void update()
		{
			//std::cout << "Update TestSystem ." << mSomeConfigSetting++ << " " << std::endl;

			if (mSomeConfigSetting > 50)
				mChannel.broadcast(core::TaskManager::StopEvent());
			

			input::TouchEvent evt;
			evt.phase = (input::TouchEvent::Phase)(rand() % 4);// input::TouchEvent::BEGAN ;
			mEngine->getInput()->getTouch()->TouchPosCallback_evt(evt);

			std::this_thread::sleep_for(std::chrono::milliseconds(100));
		}

		unsigned int mSomeConfigSetting;

		// Event handlers			
		void touchesBeganHandler(const TouchSet& touches){}
		void touchesEndedHandler(const TouchSet& touches){}
		void touchesMovedHandler(const TouchSet& touches){}


	};

	void OnActive_(int iTest)
	{
		printf("OnActive Call ");
	}

	void OnActive()
	{
		printf("OnActive Call ");
	}

	void OnSuspend()
	{
		printf("OnSuspend Call ");
	}
	
	void OnExit()
	{
		printf("OnExit Call ");
	}


}


namespace EventTest
{

	struct Explosion
	{
		explicit Explosion(int damage) : damage(damage) {}
		int damage;
	};

	struct ExplosionHandler
	{
		void handle(const Explosion& d)
		{
			std::cout << "Explosion : !" << d.damage << std::endl;
		}
	};


	struct ExplosionSystemnHandler
	{
		void receive(const Explosion &explosion)
		{
			damage_received += explosion.damage;
		}

		int damage_received = 0;

		void handle(const Explosion& d)
		{
			std::cout << "Explosion : !" << d.damage << std::endl;
		}
	};

	/*EventTest::ExplosionHandler explosion_handler;
	EventTest::Explosion _explosion(4);

	core::EventChannel chan;
	chan.add<EventTest::Explosion>(explosion_handler);


	chan.broadcast(_explosion);

	EventTest::ExplosionSystemnHandler explosion_system;
	chan.add<EventTest::Explosion>(explosion_system);
	EventTest::Explosion explosion(10);;
	chan.broadcast(explosion);*/
}


using std::ostream;
using std::vector;
using std::string;

namespace EntityTest
{
	using namespace std;
	using namespace entityx;


	template <typename T>
	int size(const T &t) {
		int n = 0;
		for (auto i : t) {
			++n;
			(void)i; // Unused on purpose, suppress warning
		}
		return n;
	}

	struct Position : Component<Position>
	{
		Position(float x = 0.0f, float y = 0.0f) : x(x), y(y) {}

		bool operator==(const Position &other) const {
			return x == other.x && y == other.y;
		}

		float x, y;
	};

	ostream &operator<<(ostream &out, const Position &position) {
		out << "Position(" << position.x << ", " << position.y << ")";
		return out;
	}

	struct Direction : Component<Direction> {
		Direction(float x = 0.0f, float y = 0.0f) : x(x), y(y) {}

		bool operator==(const Direction &other) const {
			return x == other.x && y == other.y;
		}

		float x, y;
	};

	ostream &operator<<(ostream &out, const Direction &direction) {
		out << "Direction(" << direction.x << ", " << direction.y << ")";
		return out;
	}

	struct Tag : Component<Tag> {
		explicit Tag(string tag) : tag(tag) {}

		bool operator==(const Tag &other) const { return tag == other.tag; }

		string tag;
	};

	ostream &operator<<(ostream &out, const Tag &tag) {
		out << "Tag(" << tag.tag << ")";
		return out;
	}


	struct EntityManagerFixture {
		EntityManagerFixture() : em(),sm() {}

		core::EventChannel ev;
		EntityManager em;
		SystemManager sm;
	};


	/*
	class MovementSystem : public  System<MovementSystem>
	{
	public:
		explicit MovementSystem(string label = "") : label(label) {}

		void update(EntityManager &es, core::EventChannel &events, double) override
		{
			EntityManager::View entities = es.entities_with_components<Position, Direction>();
			
			ComponentHandle<Position> position;
			ComponentHandle<Direction> direction;
			
			for (auto entity : entities) 
			{
				entity.unpack<Position, Direction>(position, direction);
				position->x += direction->x;
				position->y += direction->y;
			}
		}

		string label;
	};

	class EntitiesFixture : public EntityManagerFixture {
	public:
		std::vector<Entity> created_entities;

		EntitiesFixture() {
			for (int i = 0; i < 50; ++i) {
				Entity e = em.create();

				created_entities.push_back(e);

				if (i % 2 == 0) e.assign<Position>(1, 2);
				if (i % 3 == 0) e.assign<Direction>(1, 1);
			}
		}
	};*/

}

struct Position
{
	explicit Position(int *ptr = nullptr) : ptr(ptr) 
	{
		if (ptr) (*ptr)++;
	}
	~Position() {
		if (ptr) (*ptr)++;
	}

	float x, y;
	int *ptr;
};






int _tmain(int argc, _TCHAR* argv[])
{


	
	//EntityTest::EntitiesFixture emf;
	
	/*
	vector<entityx::Entity::Id> entities;

	struct EntityCreatedEventReceiver : public core::EventHandler<entityx::EntityCreatedEvent>
	{
		void handle(const entityx::EntityCreatedEvent &event) 
		{
			created.push_back(event.entity);
		}

		vector<entityx::Entity> created;
	};

	EntityCreatedEventReceiver receiver;
	emf.ev.add<entityx::EntityCreatedEvent>(receiver);

	assert(0UL == receiver.created.size());
	for (int i = 0; i < 10; ++i) {
		emf.em.create();
	}
	assert(10UL == receiver.created.size());
	*/
	
	/*
	 emf.sm.add<EntityTest::MovementSystem>("movement");
	 emf.sm.configure();

	 assert("movement" == emf.sm.system<EntityTest::MovementSystem>()->label);

	 emf.sm.update<EntityTest::MovementSystem>(0.0);

	 EntityTest::ComponentHandle<EntityTest::Position> position;
	 EntityTest::ComponentHandle<EntityTest::Direction> direction;

	 for (auto entity : emf.created_entities)
	 {
		 entity.unpack<EntityTest::Position, EntityTest::Direction>(position, direction);
		
		 if (position && direction)
		 {
			 assert(2.0 == (position->x));
			 assert(3.0 == (position->y));
		 }
		 else if (position)
		 {
			 assert(1.0 == (position->x));
			 assert(2.0 == (position->y));
		 }
	 }*/

	


	try {
				


		app::Application::Platform_InitFkh();
		
		static auto globalLogFile = std::make_unique<std::ofstream>("global.log");

		srand((unsigned int)time(NULL));
		//gLog.add(new std::ofstream("global.log"));
		gLog << "Starting Overdrive Assault...";


		const std::string title = "OpenGLESWindow";
		core::OpenGLESWindow::OpenGLESWindowPtr wnd(new core::OpenGLESWindow(title));
		test::TestSystem::Ptr testApp(new test::TestSystem());
		app::TestShaders::Ptr testShader(new app::TestShaders());

		Tuxis::WindowEGL::Ptr windowEGL(new Tuxis::WindowEGL(320, 480, L"Weezy App", true));


		//Entry point, main module of this framework
		core::Engine mEngine;
				
		/**/
		mEngine.windowCreationHint(core::Engine::USE_GLFW3); 
		mEngine.getVideo()->addWindow(windowEGL, title);
		//mEngine.getSystemtEntity()->add<EntityTest::MovementSystem>("movement");
		
		mEngine.getApplication()->Activating   = &test::OnActive;
		mEngine.getApplication()->Deactivating = &test::OnExit;

		app::Application::Platform_OnActive();

		mEngine.setApplication(testShader);
		mEngine.run();


		app::Application::Platform_ShutdownFkh();
		
	}
	catch (std::exception e)
	{
		std::cerr << e.what() << std::endl;
	}
	catch (...) 
	{
		std::cerr << "Unknown exception" << std::endl;
	}
	

	return 0;
}



/*
strptr = new StringTransport();

inty.i = 5;
str.message = "Testing 123";
strptr->message = "Ptr!";

broadcast("No receivers");

DummyHandler dummy_handler;
DoubleHandler double_handler;
PtrHandler ptr_handler;

chan.add<Dummy>(dummy_handler);
chan.add<IntTransport>(double_handler);
chan.add<StringTransport>(double_handler);
chan.add<StringTransport*>(ptr_handler);

broadcast("All receivers");

chan.remove<StringTransport>(double_handler);

broadcast("Minus one");

delete strptr;
*/