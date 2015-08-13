#include <algorithm>
#include "MessageQueue.h"

namespace MessageBus
{
	// Class helper find message for recepient id.
	class IsRecepientMessage
	{
	public:
		IsRecepientMessage(const GUID& receiverId) : _receiverId(receiverId) { }

		bool operator() (const IMessage *message) const
		{
			return IsEqualGUID(message->MessageReceiver(), _receiverId);
		}

	private:
		const GUID& _receiverId;
	};

	MessageQueue::MessageQueue()
	{
	}


	MessageQueue::~MessageQueue()
	{
	}

	bool MessageQueue::Subscribe(const GUID& subscriber)
	{
		bool result = false;
		_lockSubscribers.Lock();
		std::list<GUID>::iterator it = std::find(_subscribers.begin(), _subscribers.end(), subscriber);
		if (it == _subscribers.end())
		{
			_subscribers.push_back(subscriber);
			result = true;
		}

		_lockSubscribers.Unlock();
		return result;
	}

	bool MessageQueue::Unsubscribe(const GUID& subscriber)
	{
		bool result = false;
		_lockSubscribers.Lock();
		std::list<GUID>::iterator it = std::find(_subscribers.begin(), _subscribers.end(), subscriber);
		if (it != _subscribers.end())
		{
			_subscribers.remove(subscriber);
			result = true;
		}

		_lockSubscribers.Unlock();
		return result;
	}

	bool MessageQueue::IsSubscribe(const GUID& subscriber)
	{
		bool result = false;
		_lockSubscribers.Lock();
		std::list<GUID>::iterator it = std::find(_subscribers.begin(), _subscribers.end(), subscriber);
		if (it != _subscribers.end())
		{
			result = true;
		}

		_lockSubscribers.Unlock();
		return result;
	}

	IMessage *MessageQueue::PopMessage(const GUID& receiverId)
	{
		_lockQueue.Lock();

		std::list<IMessage *>::iterator it = std::find_if(_queue.begin(), _queue.end(), IsRecepientMessage(receiverId));
		if (it == _queue.end())
		{
			_lockQueue.Unlock();
			return NULL;
		}

		IMessage *result = *it;
		_queue.erase(it);
		_lockQueue.Unlock();

		return result;
	}

	bool MessageQueue::PushMessage(IMessage *message)
	{
		if (!IsSubscribe(message->MessageReceiver()))
		{
			return false;
		}

		_lockQueue.Lock();
		_queue.push_back(message);
		_lockQueue.Unlock();

		return true;
	}

	size_t MessageQueue::Size()
	{
		_lockQueue.Lock();
		size_t result = _queue.size();
		_lockQueue.Unlock();
		return result;
	}
}