#pragma once 





template<typename T>
class delegate
{

public:
	delegate(T* pT, void (T::*pFunc)()) : m_pT(pT), m_pFunc(pFunc) { }

	void invoke()
	{
		(m_pT->*m_pFunc)();
	}

private:
	T* m_pT;
	void (T::*m_pFunc)();
};


template<>
class delegate<void>
{

public:
	delegate(void(*pFunc)()): m_pFunc(pFunc) { }
	void invoke() {	(*m_pFunc)(); }

private:
	void(*m_pFunc)();
};
