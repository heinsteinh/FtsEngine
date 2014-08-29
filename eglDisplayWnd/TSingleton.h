#pragma once

#pragma once
#include <memory>
#include <mutex>

namespace core
{
	//thread_safe singleton
	template <typename T>
	class CSingleton
	{
	protected:
		CSingleton() = default;
		CSingleton(const CSingleton<T>& src) = default;
		CSingleton<T>& operator=(const CSingleton<T>& rhs) = default;

	public:
		static T& GetInstance()
		{
			std::call_once(m_onceFlag, []
			{
				m_instance.reset(new T);
			});

			return *m_instance.get();
		}

		static void FreeInstance(void);

	private:
		static std::unique_ptr<T> m_instance;
		static std::once_flag m_onceFlag;
	};

	template <typename T>
	std::unique_ptr<T> CSingleton<T>::m_instance;

	template <typename T>
	std::once_flag CSingleton<T>::m_onceFlag;


	template <class T>
	void CSingleton<T>::FreeInstance(void)
	{
		if (m_instance)
			m_instance.reset();

		m_instance = 0;
	}

}

#define CREATE_SINGLETON(class_name) \
class class_name : public core::CSingleton<class_name> {\
	friend class core::CSingleton<class_name>;