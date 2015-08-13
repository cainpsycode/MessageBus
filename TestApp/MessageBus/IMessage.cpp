#include "IMessage.h"

namespace MessageBus
{
	IMessage::IMessage(GUID const& sender, GUID const& receiver)
		: _sender(sender), _receiver(receiver)
	{
	}

	IMessage::~IMessage()
	{
	}

	const GUID& IMessage::MessageSender() const
	{
		return _sender;
	}

	const GUID& IMessage::MessageReceiver() const
	{
		return _receiver;
	}
}