#pragma once

#include <fstream>
#include "../Common/ThreadClass.h"
#include "../Common/ILogger.h"
#include "../MessageBus/MessageQueue.h"
#include "BaseClientThread.h"
#include "ReadClientThread.h"
#include "WriteClientThread.h"

namespace Test
{
	class MasterClientThread : public BaseClientThread
	{
	public:
		MasterClientThread(Common::ILogger& log, MessageBus::MessageQueue& bus, const GUID& id, const GUID& readerId1, const GUID& readerId2, const GUID& writerId);

		~MasterClientThread();

		bool IsFinished();

		bool IsFinishedChild();

	protected:
		void DispatchMessage(MessageBus::IMessage *message);

		void RoutineProcess();

	private:
		const GUID& _readerId1;
		const GUID& _readerId2;
		const GUID& _writerId;
		ReadClientThread *_reader1;
		ReadClientThread *_reader2;
		WriteClientThread *_writer;
		DWORD _state = 0;
		int _readTasks = 2;
	};
}


