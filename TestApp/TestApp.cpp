// TestApp.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "Common/SimplyConsoleLogger.h"
#include "MessageBus/MessageQueue.h"
#include "Test/MasterClientThread.h"

using namespace std;
using namespace Common;
using namespace MessageBus;

int _tmain(int argc, _TCHAR* argv[])
{
	ILogger *log = new SimplyConsoleLogger();
	log->Debug(_T("Start program."));

	GUID masterId, readerId1, readerId2, writerId;
	CLSIDFromString(_T("{210073DB-A5D2-4980-A7EB-002A6BEA51B3}"), &masterId);
	CLSIDFromString(_T("{F2748106-D7E0-485D-95E9-42E9142F39D3}"), &readerId1);
	CLSIDFromString(_T("{6A32F826-5EE2-412D-BBDF-428DDBD3F7EB}"), &readerId2);
	CLSIDFromString(_T("{3DA023BB-566A-40D2-8969-9E84C296A9D7}"), &writerId);

	MessageQueue *bus = new MessageQueue();
	Test::MasterClientThread *master = new Test::MasterClientThread(*log, *bus, masterId, readerId1, readerId2, writerId);
	size_t _lastQueueSize = 0;

	while (!master->IsFinishedChild())
	{
		Sleep(100);
		if (bus->Size() != _lastQueueSize)
		{
			log->Debug(_T("Message Queue size = %i."), bus->Size());
			_lastQueueSize = bus->Size();
		}
	}

	log->Debug(_T("Child threads has been terminated. Await master thread terminating."));
	master->Stop();
	while (!master->IsFinished())
	{
		Sleep(1000);
	}
	
	log->Debug(_T("Master thread has been terminated. Press [Enter] key for exit."));
	getchar();
	
	delete master;
	delete bus;
	delete log;

	return 0;
}