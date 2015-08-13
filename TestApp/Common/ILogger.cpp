#include "ILogger.h"
#include <tchar.h>

using namespace std;

namespace Common
{
	ILogger::ILogger() 
	{
	}

	ILogger::~ILogger()
	{
	}

	void ILogger::Debug(LPTSTR fmt, ...)
	{
		va_list args;
		va_start(args, fmt);
		Log(DEBUG_LEVEL, fmt, args);
		va_end(args);
	}

	void ILogger::Info(LPCTSTR format, ...)
	{
		va_list args;
		va_start(args, format);
		Log(INFO_LEVEL, format, args);
		va_end(args);
	}

	void ILogger::Warn(LPCTSTR format, ...)
	{
		va_list args;
		va_start(args, format);
		Log(WARN_LEVEL, format, args);
		va_end(args);
	}

	void ILogger::Error(LPCTSTR format, ...)
	{
		va_list args;
		va_start(args, format);
		Log(ERROR_LEVEL, format, args);
		va_end(args);
	}

	void ILogger::LogLevelToString(LOG_LEVEL level, LPTSTR strLevel)
	{
		switch (level)
		{
		case LOG_LEVEL::DEBUG_LEVEL:
			_tcscpy(strLevel, _T("DEBUG"));
			break;

		case LOG_LEVEL::ERROR_LEVEL:
			_tcscpy(strLevel, _T("ERROR"));
			break;

		case LOG_LEVEL::INFO_LEVEL:
			_tcscpy(strLevel, _T("INFO"));
			break;

		case LOG_LEVEL::WARN_LEVEL:
			_tcscpy(strLevel, _T("WARN"));
			break;
		}
	}
}