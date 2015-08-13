#include <tchar.h>

#include "MasterClientThread.h"
#include "MessageStart.h"
#include "MessageStop.h"
#include "MessageString.h"
#include "MessageError.h"
#include "MessageFinish.h"

using namespace Common;
using namespace MessageBus;

namespace Test
{
	
	MasterClientThread::MasterClientThread(ILogger& log, MessageQueue& bus, const GUID& id, const GUID& readerId1, const GUID& readerId2, const GUID& writerId)
		: BaseClientThread(log, bus, id, 50, _T("Master")),
		_readerId1(readerId1),
		_readerId2(readerId2),
		_writerId(writerId)
	{
		_reader1 = new ReadClientThread(_log, _bus, _readerId1, _clientId, 200, _T("Reader1"));
		_reader2 = new ReadClientThread(_log, _bus, _readerId2, _clientId, 300, _T("Reader2"));
		_writer = new WriteClientThread(_log, _bus, _writerId, _clientId, 100, _T("Writer"));
	}

	MasterClientThread::~MasterClientThread()
	{
		delete _reader1;
		delete _reader2;
		delete _writer;
	}

	bool MasterClientThread::IsFinished()
	{
		return (IsFinishedChild() && _finished);
	}

	bool MasterClientThread::IsFinishedChild()
	{
		return (_reader1->IsFinished() && _reader2->IsFinished() && _writer->IsFinished());
	}

	void MasterClientThread::DispatchMessage(IMessage *message)
	{
		switch (message->MessageId())
		{
			// Message from child thread process
		case Test::Messages::MessageString::MessageID:
		{
			Test::Messages::MessageString *msg = dynamic_cast<Test::Messages::MessageString *>(message);
			_bus.PushMessage(new Test::Messages::MessageString(_clientId, _writerId, msg->FileString()));
		}
			break;

			// Finish read file message process
		case Test::Messages::MessageFinish::MessageID:
		{
			_bus.PushMessage(new Test::Messages::MessageStop(_clientId, message->MessageSender()));
			_readTasks--;
			if (_readTasks == 0)
			{
				_bus.PushMessage(new Test::Messages::MessageStop(_clientId, _writerId));
			}
		}
			break;

			// Error message process
		case Test::Messages::MessageError::MessageID:
		{
			Test::Messages::MessageError *msg = dynamic_cast<Test::Messages::MessageError *>(message);
			_log.Error(_T("Receive error message: %s"), msg->ErrorDescription().c_str());
			_log.Warn(_T("Send signal of terminate to all child threads."));
			_bus.PushMessage(new Test::Messages::MessageStop(_clientId, _readerId1));
			_bus.PushMessage(new Test::Messages::MessageStop(_clientId, _readerId2));
			_bus.PushMessage(new Test::Messages::MessageStop(_clientId, _writerId));
		}
			break;
		}
	}

	void MasterClientThread::RoutineProcess()
	{
		// statemachine
		switch (_state)
		{
			// start read from files
		case 0:
			_bus.PushMessage(new Test::Messages::MessageStart(_clientId, _writerId, _T("output.txt")));
			_bus.PushMessage(new Test::Messages::MessageStart(_clientId, _readerId1, _T("Spielberg.txt")));
			_bus.PushMessage(new Test::Messages::MessageStart(_clientId, _readerId2, _T("Lynch.txt")));
			_state = 1;
			break;

		case 1:
			break;
		}
	}
}