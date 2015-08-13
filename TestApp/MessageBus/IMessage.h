#pragma once

#include "rpc.h"

namespace MessageBus
{
	class IMessage
	{
	public:
		IMessage(GUID const& sender, GUID const& receiver);

		virtual ~IMessage();

		virtual DWORD MessageId() const = 0;

		const GUID &MessageSender() const;

		const GUID &MessageReceiver() const;

	protected:
		const GUID _sender;
		const GUID _receiver;
	};
}