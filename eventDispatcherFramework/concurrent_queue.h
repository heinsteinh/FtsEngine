#include <queue>
#include <thread>
#include <thread>
#include <memory>
#include <mutex>
#include <condition_variable>




template <typename T>
class ConcurrentQueue {
private:
	typedef std::queue<T> Queue;
	typedef std::mutex Mutex;
	typedef std::unique_lock<std::mutex> ScopedLock;

	typedef std::condition_variable Condition;

public:
	bool empty() const;
	void push(const T& value);
	bool try_pop(T& result);
	T wait_pop();
	std::size_t size() const;

private:
	Queue mQueue;
	mutable Mutex mMutex;
	Condition mCondition;
};

/* implementation */
template <typename T>
bool ConcurrentQueue<T>::empty() const {
	ScopedLock lock(mMutex);
	return mQueue.empty();
}

template <typename T>
std::size_t ConcurrentQueue<T>::size() const 
{
	ScopedLock lock(mMutex);
	return mQueue.size();
}

template <typename T>
void ConcurrentQueue<T>::push(const T& value) 
{
	
	{
		ScopedLock lock(mMutex);
		mQueue.push(value);
	}


	mCondition.notify_one();
}

template <typename T>
bool ConcurrentQueue<T>::try_pop(T& result) {
	
	ScopedLock lock(mMutex);
	if (mQueue.empty())
		return false;

	result = mQueue.front();
	mQueue.pop();

	return true;
}

template <typename T>
T ConcurrentQueue<T>::wait_pop() {
	ScopedLock lock(mMutex);

	while (mQueue.empty())
		mCondition.wait(lock, [this]{return !mQueue.empty(); });
		//mCondition.wait(lock);

	T result(mQueue.front());
	mQueue.pop();

	return result;
}



