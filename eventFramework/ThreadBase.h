#pragma once



namespace  BubbleBattleBoids
{


	class Runnable {
	public:
		virtual void run() = 0;
	};

	class ThreadBody;

	class Thread
	{

	private:
		ThreadBody *pImpl;

	public:
		Thread(Runnable *);

		~Thread();
	};
}

