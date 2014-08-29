#pragma once


namespace ANAS
{


	class Runnable {
	public:
		virtual void run() = 0;
	};

	class ThreadBody;

	class Thread
	{

	private:
		ANAS::ThreadBody *pImpl;

	public:	
		Thread(Runnable *);
		
		~Thread();
	};
}

