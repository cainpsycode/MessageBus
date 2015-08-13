#include <tchar.h>
#include <fstream>
#include "ReadClientThread.h"
#include "MessageStart.h"
#include "MessageStop.h"
#include "MessageString.h"
#include "MessageFinish.h"
#include "MessageError.h"
#include "BaseClientThread.h"

using namespace Common;
using namespace MessageBus;

namespace Test
{
	ReadClientThread::ReadClientThread(ILogger& log, MessageQueue& bus, const GUID& id, const GUID& masterId, int awaitTimeoutMs, const wstring &clientName)
		: BaseClientThread(log, bus, id, awaitTimeoutMs, clientName),
		_masterId(masterId)
	{
	}

	void ReadClientThread::DispatchMessage(IMessage *message)
	{
		
		DWORD msgId = message->MessageId();
		switch (msgId)
		{
			case Messages::MessageStart::MessageID:
			{
				Test::Messages::MessageStart *m = dynamic_cast<Test::Messages::MessageStart *>(message);
				_infile.open(m->FilePath(), std::fstream::in);
				if (_infile.is_open())
				{
					_state = 1;
				}
				else
				{
					_bus.PushMessage(new Test::Messages::MessageError(_clientId, _masterId, _T("error opening input file")));
				}
			}
			break;

			case Test::Messages::MessageStop::MessageID:
			{
				_bus.Unsubscribe(_clientId);
				_state = -1;
				_stopped = true;
			}
			break;
		}
	}

	void ReadClientThread::RoutineProcess()
	{
		// State machine
		switch (_state)
		{
			case 0:
				break;

			case 1:
			{
				string strLine;
				if (getline(_infile, strLine))
				{
					_bus.PushMessage(new Test::Messages::MessageString(_clientId, _masterId, wstring(strLine.begin(), strLine.end())));
				}
				else
				{
					_infile.close();
					_bus.PushMessage(new Test::Messages::MessageFinish(_clientId, _masterId));
					_state = -1;
				}
				break;
			}
		}
	}
}