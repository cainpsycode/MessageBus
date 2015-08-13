#pragma once

#include <Windows.h>

namespace Common
{
	namespace Threading
	{
		class ThreadClass
		{
		public:
			ThreadClass() { }

			virtual ~ThreadClass();

			bool CreateNewThread();

			// Suspend the thread.
			bool Suspend();

			// Resume a suspended thread.
			bool Resume();

			// Terminate a thread.
			bool Kill();

			// Wait for thread to end.
			bool Wait();

			// Check for activity.
			bool IsActive();

			// override these functions in the derived class 
			virtual void ThreadEntry() { }

			virtual void ThreadExit() { }

			virtual void Run() { }

			// a friend routine func
			friend DWORD WINAPI _ThreadFunc(LPVOID pvThread);

		protected:
			HANDLE _threadHandle;
			bool _active;
			DWORD _threadId;
		};
	}
}