#ifndef THREAD_SAFE_QUEUE_INCLUDED
#define THREAD_SAFE_QUEUE_INCLUDED

#include <queue>
#include <vector>
#include <deque>

#include <thread>
#include <mutex>
#include <condition_variable>
#include <memory>


template<typename T>
class threadsafe_queue
{
private:
	mutable std::mutex mut;
	std::queue<std::shared_ptr<T> > data_queue;
	std::condition_variable data_cond;
public:
	threadsafe_queue()
	{}

	void wait_and_pop(T& value)
	{
		std::unique_lock<std::mutex> lk(mut);
		data_cond.wait(lk, [this]{return !data_queue.empty(); });
		value = std::move(*data_queue.front());
		data_queue.pop();
	}

	bool try_pop(T& value)
	{
		std::lock_guard<std::mutex> lk(mut);
		if (data_queue.empty())
			return false;
		value = std::move(*data_queue.front());
		data_queue.pop();
	}

	std::shared_ptr<T> wait_and_pop()
	{
		std::unique_lock<std::mutex> lk(mut);
		data_cond.wait(lk, [this]{return !data_queue.empty(); });
		std::shared_ptr<T> res = data_queue.front();
		data_queue.pop();
		return res;
	}

	std::shared_ptr<T> try_pop()
	{
		std::lock_guard<std::mutex> lk(mut);
		if (data_queue.empty())
			return std::shared_ptr<T>();
		std::shared_ptr<T> res = data_queue.front();
		data_queue.pop();
		return res;
	}

	bool empty() const
	{
		std::lock_guard<std::mutex> lk(mut);
		return data_queue.empty();
	}

	int size() const
	{
		std::lock_guard<std::mutex> lk(mut);
		return data_queue.size();
	}
	
	

	void push(T new_value)
	{
		std::shared_ptr<T> data(
			std::make_shared<T>(std::move(new_value)));
		std::lock_guard<std::mutex> lk(mut);
		data_queue.push(data);
		data_cond.notify_one();
	}

};



template <typename T>
class ThreadSafeQueue
{
private:
	mutable std::mutex mtx_;
	std::queue<T> queue_;
	std::condition_variable condition_;

public:
	ThreadSafeQueue()
	{
	}

	ThreadSafeQueue(const ThreadSafeQueue& other)
	{
		std::lock_guard< std::mutex > lk(other.mtx_);
		queue_ = other.queue_;
	}

	void push(T value)
	{
		std::lock_guard< std::mutex > lk(mtx_);
		queue_.push(value);

		condition_.notify_one();
	}

	void wait_and_pop(T& value)
	{
		std::unique_lock< std::mutex > lk(mtx_);

		condition_.wait(lk, !std::bind(&std::queue<T>::empty, std::ref(queue_)));
		value = queue_.front();
		queue_.pop();
	}

	std::shared_ptr<T> wait_and_pop()
	{
		std::unique_lock< std::mutex > lk(mtx_);

		condition_.wait(lk, !std::bind(&std::queue<T>::empty, std::ref(queue_)));
		std::shared_ptr<T> result(new T(queue_.front()));
		queue_.pop();

		return result;
	}

	bool try_pop(T& value)
	{
		std::lock_guard< std::mutex > lk(mtx_);

		if (queue_.empty())
			return false;

		value = queue_.front();
		queue_.pop();

		return true;
	}

};

#endif // THREAD_SAFE_QUEUE_INCLUDED
