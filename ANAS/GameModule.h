#pragma once
#include "MyWindow.h"
#include "TaskScheduler.h"
#include "ThreadSync.h"


#include "Input.h"

//https://github.com/OhHey/OhHeyProject/blob/fcecb92eb204512db8faf3a292ba5c8d3630df80/main.cpp
namespace win
{
	class GameModule   : core::TaskManager, public ANAS::Signal
	{
	public:

		GameModule(HINSTANCE &instance);

		void Shutdown(void);
		void Show(bool show);
		bool MainLoop(MSG* arg);
		float time1, time2;

		InputStruct theinput;

		std::thread MainThread;

		void StartGame();
	private:
		HINSTANCE instance;
		windowclass thewindow;
		HWND window;

		

	private:
		ANAS::Input*  mInput;;

		//GraphicsModule graphics;
	};

}

