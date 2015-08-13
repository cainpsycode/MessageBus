#include <tchar.h>
#include "SimplyConsoleLogger.h"
#include "ILogger.h"

namespace Common
{
	SimplyConsoleLogger::SimplyConsoleLogger()
	{
	}


	SimplyConsoleLogger::~SimplyConsoleLogger()
	{
	}

	void SimplyConsoleLogger::Log(ILogger::LOG_LEVEL level, LPCTSTR format, va_list const args)
	{
		TCHAR strDate[10] = { _T('\0') };
		TCHAR strTime[10] = { _T('\0') };
		TCHAR strLevel[10];

		_tstrdate_s(strDate, 10);
		_tstrtime_s(strTime, 10);
		LogLevelToString(level, strLevel);

		_tprintf(_T("[%s %s] [%s] "), strDate, strTime, strLevel);
		_vtprintf(format, args);
		_tprintf(_T("\n"));
	}
}