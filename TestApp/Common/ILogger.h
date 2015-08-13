#pragma once

#include <windows.h>

using namespace std;

namespace Common 
{
	class ILogger
	{
	public:
		enum LOG_LEVEL { DEBUG_LEVEL, INFO_LEVEL, WARN_LEVEL, ERROR_LEVEL };

		ILogger();

		~ILogger();

		void Debug(LPTSTR fmt, ...);

		void Info(LPCTSTR format, ...);

		void Warn(LPCTSTR format, ...);

		void Error(LPCTSTR format, ...);

	protected:
		virtual void Log(LOG_LEVEL level, LPCTSTR format, va_list args) = 0;

		void LogLevelToString(LOG_LEVEL level, LPTSTR strLevel);

	};
}