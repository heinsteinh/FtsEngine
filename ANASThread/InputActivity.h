#pragma once



#include "TaskScheduler.h"
#include "SignalThread.h"

#include <map>
#include <queue>
#include <vector>
#include <list>

namespace ANAS
{

	namespace InputData
	{

		enum LooperEventID {
			MAIN_ID = 1,
			INPUT_ID = 2,
			USER_ID = 3,
		};


		typedef struct InputData_tag
		{
			int InputType;

			// KeyState
			int KeyChar;
			bool isLong;

			// MotionState
			//ANAS::Vector2 Pos;
			int ActionType;
		} InputData;


		enum Key
		{
			eUp,
			eDown,
			eLeft,
			eRight
		};

		enum Action
		{
			kMoveUp,
			kMoveDown,
			kMoveLeft,
			kMoveRight,

			kClose
		};

		struct Event
		{
			Action action;
			bool pressed;
		};


		class TaskKey : public Task
		{

		public:
			typedef std::function<bool(const Event&evt)> Holder;

			TaskKey(TaskKey::Holder& eventAction)
			{
				any_task_holder = eventAction;
			}


			inline void Run()
			{
				any_task_holder(evt);
			}


		private:
			Holder any_task_holder;
			Event evt;
			Action act;
		};
	}



	class AInputQueue;
	class InputActivity  : public Signal
	{

		private:
		// for thread
		typedef	std::shared_ptr<std::thread> THREAD_PTR;
		THREAD_PTR	PollThread;
		
		bool	isLive;
		std::mutex	Mutex;

		std::list<InputData::InputData> EventStack;
	
		//thread_safe_queue<InputData::InputData> EventStack;

		int offset_x;
		int offset_y;


	public:

		

		InputActivity();
		~InputActivity();
				
		
		
		void Init(AInputQueue *pInput);
		
		void Poll();
		
		void Term();


		InputData::InputData PopState();
		void SendEvent(InputData::InputData& evtData);
		
		
		void SetScreenOffset(int, int);


	//	void MapKeyToAction(InputData::Key&, InputData::Action&);
	//	
	//	bool SendEvent(const InputData::TaskKey::Holder& evt);
	//	void SendEvent(InputData::Key ekey, bool pressed);
	//	bool SendEvent(const InputData::Event& evt);

	//private:
	//	std::map<InputData::Key, InputData::Action> key_map_;
	//	std::queue<InputData::Event> event_queue_;
	//


	//	bool SendEventTask(const InputData::TaskKey::Holder& evt);
	//	//std::vector<InputListener *> listeners_;
	};
}
