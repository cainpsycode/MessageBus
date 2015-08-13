#include "ThreadLock.h"

namespace Common
{
	namespace Threading
	{
		ProcessLock::ProcessLock()
		{
			InitializeCriticalSection(&_cs);
		}

		ProcessLock::~ProcessLock()
		{
			DeleteCriticalSection(&_cs);
		}

		bool ProcessLock::TryLock()
		{
			return TryEnterCriticalSection(&_cs) > 0 ? true : false;
		}

		void ProcessLock::Lock()
		{
			EnterCriticalSection(&_cs);
		}

		void ProcessLock::Unlock()
		{
			return LeaveCriticalSection(&_cs);
		}
	}
}