#pragma once


namespace Framework
{
	
	class Runnable {
	public:
		virtual void Run() = 0;
	};

	class ThreadBody;

	class Thread
	{

	private:
		 Framework::ThreadBody *pImpl;

	public:
		Thread(Runnable *);

		~Thread();
	};
}