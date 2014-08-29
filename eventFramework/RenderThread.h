#pragma once


#include <thread>
#include <queue>
#include <functional>
#include <memory>
#include <condition_variable>


namespace  BubbleBattleBoids
{


	class GameObject;
	class Message
	{
	public:
		Message(int type) : type(type) {}
		virtual ~Message() {}
		int type;
	};

	class KillObjectMsg : public Message
	{
	public:
		static const unsigned id = 0;
		KillObjectMsg(GameObject* object) : Message(0), object(object) {}
		GameObject* object;
	};


	class RenderThread
	{
	public:
		RenderThread();
		~RenderThread();

		typedef std::function<void()> Job;
		void Send(Job job);

		//void Send(const Message& job);
		void CleanUp();

	private:
		void thrmain();

		std::unique_ptr<std::thread> m_thr;
		bool m_isCancelled;


		std::mutex m_mtxJobs;
		std::condition_variable m_condJobArrival;
		std::queue<Job> m_jobq;



		// Dead objects are sent here by main thread for render thread to clean up on its own time
		std::vector<GameObject*> mDeadObjects;

	};

} // end of namespace ptnk