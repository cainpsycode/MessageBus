#include "ThreadClass.h"

namespace Common
{
	namespace Threading
	{
		bool ThreadClass::CreateNewThread()
		{
			_threadHandle = CreateThread(
				NULL,
				0,
				(LPTHREAD_START_ROUTINE)_ThreadFunc,
				(LPVOID) this,
				0,
				(LPDWORD)&_threadId);

			if (_threadHandle == NULL)
			{
				return false;
			}

			_active = true;
			return true;
		}

		ThreadClass::~ThreadClass()
		{
			Kill();
		}

		bool ThreadClass::Suspend()
		{
			_active = false;
			return (SuspendThread(_threadHandle) != -1);
		}

		bool ThreadClass::Resume()
		{
			_active = true;
			return(ResumeThread(_threadHandle) != -1);
		}

		bool ThreadClass::Kill()
		{
			return (TerminateThread(_threadHandle, 1) == 0);
		}

		bool ThreadClass::Wait()
		{
			return (WaitForSingleObject(_threadHandle, INFINITE) == WAIT_OBJECT_0);
		}

		bool ThreadClass::IsActive()
		{
			return _active;
		}

		// Friend of Thread class
		DWORD WINAPI _ThreadFunc(LPVOID pvThread)
		{
			ThreadClass* pThread = (ThreadClass*)pvThread;
			pThread->ThreadEntry();
			pThread->Run();
			pThread->ThreadExit();
			return 0;
		}
	}
}