#pragma once
#include <Windows.h>

namespace Common
{
	namespace Threading
	{
		class ProcessLock
		{
		public:
			ProcessLock();

			~ProcessLock();

			bool TryLock();

			void Lock();

			void Unlock();

		private:
			CRITICAL_SECTION _cs;
		};
	}
}