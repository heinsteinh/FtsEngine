#pragma once

class IRunnable
{
public:
	virtual void run() = 0;
};


class Thread
{
	HANDLE m_handle;
	DWORD m_threadId;
	IRunnable* m_pRunnable;

	static DWORD WINAPI threadProc(LPVOID data);
public:
	Thread(IRunnable* r);
	void start();
	void suspend();


	inline void TRACE(const char * pszFormat, ...)
	{
		va_list pArgs;
		char szMessageBuffer[16380] = { 0 };
		va_start(pArgs, pszFormat);
		vsnprintf_s(szMessageBuffer, 16380, 16380 - 1, pszFormat, pArgs);
		va_end(pArgs);
		OutputDebugStringA(szMessageBuffer);
	}

};
