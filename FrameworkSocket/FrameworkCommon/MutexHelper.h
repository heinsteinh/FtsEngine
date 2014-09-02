#pragma once

#include <thread>
#include <mutex>
#include <map>


namespace Framework
{

	struct MutexState
	{
		std::thread::id m_iThread;
		size_t m_iLocks;
	};

	class MutexHelper
	{
	private:
		std::mutex *m_piMutex;
		static std::mutex m_iListMutex;
		static bool inited;
		static std::map<std::mutex*, MutexState> m_mList;
	public:
		static void Init();
		MutexHelper(std::mutex *p_piMutex);
		~MutexHelper();
	};



}