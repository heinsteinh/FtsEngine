#pragma once


#include "TaskScheduler.h"
#include "SignalThread.h"



namespace ANAS 
{


	class ANativeWindow;
	class Graphic : public TaskScheduler, public Signal 
	{

	private:
	public:

		static int Width;
		static int Height;

		Graphic();
		~Graphic();

		
		void Init(ANativeWindow *_window);

		
		void Term();

	
		void Swap(float r, float g, float b, float a);

		
		void InitTask();
	
		void TermTask();
	
		void SwapTask(float r, float g, float b, float a);
	};
}