#pragma once
#include "ThreadSync.h"
#include <list>


#include <Windows.h> //MSG

namespace ANAS 
{
	typedef struct Vector2_	
	{
		int x;
		int y;
	}Vector2;

	typedef struct InputData_tag
	{
		int InputType;

		// KeyState
		int KeyChar;
		bool isLong;

		// MotionState
		ANAS::Vector2 Pos;
		int ActionType;
	} InputData;



	class AInputQueue;
	class Input : public Signal
	{
	private:
		// for thread
		typedef	std::shared_ptr<std::thread> THREAD_PTR;
		THREAD_PTR	PollThread;
		bool	isLive;
		std::mutex	Mutex;

		MSG		*pInputQueue;


		std::list<InputData> EventStack;

		int offset_x;
		int offset_y;


	public:
		Input();
		~Input();

		void Init(MSG* pInput);


		void Poll();

	
		void Term();


		InputData PopState();

		
		void SetScreenOffset(int, int);


		bool ISsAlive(){ return isLive; }
	};


}

