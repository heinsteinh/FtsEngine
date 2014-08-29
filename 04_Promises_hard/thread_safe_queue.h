#ifndef THREAD_SAFE_QUEUE_HPP_
#define THREAD_SAFE_QUEUE_HPP_

#include <queue>
#include <thread>
#include <functional>
#include <condition_variable>
#include <mutex>
#include <memory>

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
		std::lock_guard<std::mutex> lk(other.mtx_);
		queue_ = other.queue_;
	}

	void push(T value)
	{
		std::lock_guard<std::mutex> lk(mtx_);
		queue_.push(value);
		condition_.notify_one();
	}

	void wait_and_pop(T& value)
	{
		std::unique_lock<std::mutex> lk(mtx_);
		condition_.wait(lk, !std::bind(&std::queue<T>::empty, std::ref(queue_)));
		value = queue_.front();
		queue_.pop();
	}

	std::shared_ptr<T> wait_and_pop()
	{
		std::unique_lock<std::mutex> lk(mtx_);
		condition_.wait(lk, [this]{return !queue_.empty(); });		

		std::shared_ptr<T> result(new T(queue_.front()));
		queue_.pop();
		return result;
	}

	bool try_pop(T& value)
	{
		std::lock_guard<std::mutex> lk(mtx_);
		if (queue_.empty())
			return false;
		value = queue_.front();
		queue_.pop();
	}

	std::shared_ptr<T> try_pop()
	{
		std::unique_lock<boost::mutex> lk(mtx_);
		if (queue_.empty())
			return std::shared_ptr<T>(new T(queue_.front()));

		std::shared_ptr<T> result(new T(queue_.front()));
		queue_.pop();
		return result;
	}

	bool empty() const
	{
		std::lock_guard<std::mutex> lk(mtx_);
		return queue_.empty();
	}
};

#endif /* THREAD_SAFE_QUEUE_HPP_ */