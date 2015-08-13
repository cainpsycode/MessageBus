#pragma once

#include <list>
#include "IMessage.h"
#include "../Common/ThreadLock.h"

using namespace std;

namespace MessageBus
{

	class MessageQueue
	{
	private:
		std::list<IMessage *> _queue;
		std::list<GUID> _subscribers;
		Common::Threading::ProcessLock _lockQueue;
		Common::Threading::ProcessLock _lockSubscribers;

	public:
		MessageQueue();

		~MessageQueue();

		bool Subscribe(const GUID & subscriber);

		bool Unsubscribe(const GUID& subscriber);

		bool IsSubscribe(const GUID& subscriber);

		IMessage *PopMessage(const GUID& receiverId);

		bool PushMessage(IMessage *message);

		size_t Size();
	};
}