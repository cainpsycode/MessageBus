#include "MessageStop.h"
#include <tchar.h>

namespace Test
{
	namespace Messages
	{
		MessageStop::MessageStop(GUID sender, GUID receiver)
			: IMessage(sender, receiver)
		{
		}

		MessageStop::~MessageStop()
		{
		}

		DWORD MessageStop::MessageId() const
		{
			return MessageID;
		}
	}
}
