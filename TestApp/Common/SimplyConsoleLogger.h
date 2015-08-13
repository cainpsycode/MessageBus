#pragma once
#include "ILogger.h"

namespace Common
{
	class SimplyConsoleLogger : public ILogger
	{
	public:
		SimplyConsoleLogger();
		~SimplyConsoleLogger();

	protected:
		virtual void Log(LOG_LEVEL level, LPCTSTR format, va_list const args);
	};
}