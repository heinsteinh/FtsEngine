// 04_Promises_hard.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include "thread_safe_queue.h"

#include <iostream>
#include <string>
#include <thread>
#include <future>
#include <chrono>

#include <iostream>
#include <fstream>

class AsyncIO
{
public:
	typedef std::string ResultType;
	typedef std::promise<ResultType> PromiseType;
	//typedef boost::detail::thread_move_t<boost::unique_future<ResultType> > UniqueFutureMoveableType;

	class IORequest
	{
		std::streambuf* input_stream_;
		std::shared_ptr<PromiseType> promise_;

	public:
		explicit IORequest(std::streambuf& input_stream)
			: input_stream_(&input_stream), promise_(new PromiseType())
		{
		}

		IORequest() : input_stream_(NULL)
		{
		}

		std::shared_future<ResultType> get_future()
		{
			return std::shared_future<ResultType>(promise_->get_future());
		}

		void process()
		{
			if (!promise_)
			{
				std::cout << "Pusty obiekt IORequest" << std::endl;

				return;
			}

			std::cout << "Reading a file..." << std::endl;
			try
			{
				std::string buffer;
				char ch;

				while (input_stream_->sgetc() != EOF)
				{
					ch = input_stream_->sbumpc();
					buffer += ch;
				}

				std::cout << "Reading a file finished..." << std::endl;
				promise_->set_value(buffer);
			}
			catch (...)
			{
				promise_->set_exception(std::current_exception());
			}
		}
	};

private:
	ThreadSafeQueue<IORequest> request_queue_;
	bool done_;
	std::mutex mtx_;
	std::thread io_thd;

	void io_thread()
	{
		std::cout << "Starting io_thread()" << std::endl;
		std::unique_lock<std::mutex> lk(mtx_, std::defer_lock);
		while (true)
		{
			lk.lock();
			if (done_)
			{
				std::cout << "done_ is true" << std::endl;
				break;
			}
			lk.unlock();

			std::shared_ptr<IORequest> req(request_queue_.wait_and_pop());
			std::cout << "IORequest popped from a queue..." << std::endl;
			req->process();
		}
		std::cout << "End of io_thread()" << std::endl;
	}

public:
	AsyncIO() : done_(false), io_thd(&AsyncIO::io_thread, this)
	{
	}

	~AsyncIO()
	{
		std::cout << "~AsyncIO" << std::endl;
		std::unique_lock<std::mutex> lk(mtx_);
		done_ = true;
		lk.unlock();

		request_queue_.push(IORequest());
		io_thd.join();
	}

	std::shared_future<ResultType> queue_read(std::streambuf& input_stream)
	{
		IORequest req(input_stream);
		std::shared_future<ResultType> future(req.get_future());
		request_queue_.push(req);
		return future;
	}
};

void do_stuff()
{
	std::cout << "do_stuff() is working" << std::endl;
	for (int i = 0; i < 10; ++i)
	{
		std::this_thread::sleep_for(std::chrono::microseconds(250));
		std::cout << ".";
		std::cout.flush();
	}
	std::cout << std::endl;
}

void process_data(const std::string& str)
{
	std::cout << "Processing:\n";
	std::cout << str << std::endl;
}

int _tmain(int argc, _TCHAR* argv[])
{

	AsyncIO async_io;

	std::filebuf f1;


	f1.open("promises.cpp", std::ios::in);

	std::filebuf f2;
	f2.open("thread_safe_queue.hpp", std::ios::in);

	std::vector<std::shared_future<std::string> > contents;

	contents.push_back(async_io.queue_read(f1));
	contents.push_back(async_io.queue_read(f2));


	do_stuff();

	process_data(contents[0].get());
	process_data(contents[1].get());
	return 0;
}

