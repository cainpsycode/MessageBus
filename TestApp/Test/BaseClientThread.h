#pragma once

#include "../Common/ThreadClass.h"
#include "../Common/ILogger.h"
#include "../MessageBus/MessageQueue.h"

namespace Test
{
	class BaseClientThread : protected Common::Threading::ThreadClass
	{
	public:
		BaseClientThread(Common::ILogger& log, MessageBus::MessageQueue& bus, const GUID& id, int awaitTimeoutMs, const wstring &clientName);

		virtual ~BaseClientThread();

		virtual bool IsFinished();

		virtual void Stop();

	protected:
		virtual void DispatchMessage(MessageBus::IMessage *message) = 0;
		virtual void RoutineProcess() = 0;

	private:
		virtual void ThreadEntry();

		virtual void ThreadExit();

		virtual void Run();

	protected:
		Common::ILogger& _log;
		MessageBus::MessageQueue& _bus;
		const GUID _clientId;
		const wstring _clientName;
		bool _finished = false;
		bool _stopped = false;
		int _awaitTimeoutMs;
	};
}


