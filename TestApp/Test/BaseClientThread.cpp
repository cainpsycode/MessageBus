#include "BaseClientThread.h"
#include <tchar.h>

using namespace Common;
using namespace MessageBus;

namespace Test
{
	BaseClientThread::BaseClientThread(Common::ILogger& log, MessageBus::MessageQueue& bus, const GUID& id, int awaitTimeoutMs, const wstring &clientName)
			: _log(log), _bus(bus), _clientId(id), _awaitTimeoutMs(awaitTimeoutMs), _clientName(clientName)
	{
		_bus.Subscribe(_clientId);
		CreateNewThread();
	}

	BaseClientThread::~BaseClientThread()
	{
		_bus.Unsubscribe(_clientId);
		Stop();
	}

	bool BaseClientThread::IsFinished()
	{
		return _finished;
	}

	void BaseClientThread::Stop()
	{
		_stopped = true;
		Wait();
	}

	void BaseClientThread::ThreadEntry()
	{
		_finished = false;
		_log.Debug(_T("[%s] Thread %i - entry."), _clientName.c_str(), _threadId);
	}

	void BaseClientThread::ThreadExit()
	{
		_finished = true;
		_log.Debug(_T("[%s] Thread %i - exit."), _clientName.c_str(), _threadId);
	}

	void BaseClientThread::Run()
	{
		_log.Debug(_T("[%s] Thread %i - run."), _clientName.c_str(), _threadId);
		while (!_stopped)
		{
			IMessage* msg = _bus.PopMessage(_clientId);
			if (msg != NULL)
			{
				_log.Debug(_T("[%s] - has received message [%i]."), _clientName.c_str(), msg->MessageId());
				DispatchMessage(msg);
				delete msg;
			}

			Sleep(_awaitTimeoutMs);
			RoutineProcess();
		}
	}

}