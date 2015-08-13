#include <tchar.h>
#include <fstream>

#include "WriteClientThread.h"
#include "MessageStart.h"
#include "MessageStop.h"
#include "MessageString.h"
#include "MessageError.h"

using namespace Common;
using namespace MessageBus;

namespace Test
{
	WriteClientThread::WriteClientThread(ILogger& log, MessageQueue& bus, const GUID& id, const GUID& masterId, int awaitTimeoutMs, const wstring &clientName)
			: BaseClientThread(log, bus, id, awaitTimeoutMs, clientName),
			_masterId(masterId)
	{
	}

	void WriteClientThread::DispatchMessage(IMessage *message)
	{
		switch (message->MessageId())
		{
		case Test::Messages::MessageStart::MessageID:
		{
			Test::Messages::MessageStart *m = dynamic_cast<Test::Messages::MessageStart *>(message);
			_outFile.open(m->FilePath(), std::fstream::out);
		}
			break;

		case Test::Messages::MessageString::MessageID:
		{
			Test::Messages::MessageString *msg = dynamic_cast<Test::Messages::MessageString *>(message);
			if (_outFile.is_open())
			{
				wstring text = msg->FileString();
				_log.Info(_T("WRITE TO FILE %s"), text.c_str());
				_outFile << string(text.begin(), text.end()) << endl;
			}
			else
			{
				_bus.PushMessage(new Test::Messages::MessageError(_clientId, _masterId, _T("error opening output file")));
			}

			break;
		}

		case Test::Messages::MessageStop::MessageID:
		{
			_outFile.close();
			_bus.Unsubscribe(_clientId);
			_stopped = true;
			break;
		}
		}
	}

	void WriteClientThread::RoutineProcess()
	{
	}
}