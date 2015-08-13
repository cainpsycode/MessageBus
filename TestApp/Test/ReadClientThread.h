#pragma once

#include "../Common/ThreadClass.h"
#include "../Common/ILogger.h"
#include "../MessageBus/MessageQueue.h"
#include "BaseClientThread.h"

namespace Test
{
	class ReadClientThread : public BaseClientThread
	{
	public:
		ReadClientThread(Common::ILogger& log, MessageBus::MessageQueue& bus, const GUID& id, const GUID& masterId, int awaitTimeoutMs, const wstring &clientName);

	protected:
		void DispatchMessage(MessageBus::IMessage *message);

		void RoutineProcess();

	private:
		DWORD _state = 0;
		wstring _filePath;
		const GUID& _masterId;
		ifstream _infile;
	};
}


