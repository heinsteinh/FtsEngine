
#ifndef _ptnk_helperthr_h_
#define _ptnk_helperthr_h_

#include <mutex>
#include <condition_variable>
#include <memory>
#include <thread>
#include <queue>
#include <functional>

//https://github.com/nyaxt/ptnk/blob/eab15a153f6b6077d1b1309a78d0f21ad9bdc39a/ptnk/helperthr.h

namespace core
{

	class Helper
	{
	public:
		Helper();
		~Helper();

		typedef std::function<void()> Job;
		void enq(Job job);

	private:
		void thrmain();

		std::unique_ptr<std::thread> m_thr;
		bool m_isCancelled;

		std::mutex m_mtxJobs;
		std::condition_variable m_condJobArrival;
		std::queue<Job> m_jobq;
	};

} // end of namespace core

#endif // _ptnk_helperthr_h_