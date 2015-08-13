#pragma once

#include <fstream>
#include "../Common/ThreadClass.h"
#include "../Common/ILogger.h"
#include "../MessageBus/MessageQueue.h"
#include "BaseClientThread.h"

namespace Test
{
	class WriteClientThread : public BaseClientThread
	{
	public:
		WriteClientThread(Common::ILogger& log, MessageBus::MessageQueue& bus, const GUID& id, const GUID& masterId, int awaitTimeoutMs, const wstring &clientName);

	protected:
		void DispatchMessage(MessageBus::IMessage *message);

		void RoutineProcess();

	private:
		const GUID& _masterId;
		ofstream _outFile;
	};
}


