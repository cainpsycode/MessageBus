#include "MessageFinish.h"
#include <tchar.h>

namespace Test
{
	namespace Messages
	{
		MessageFinish::MessageFinish(GUID sender, GUID receiver)
			: IMessage(sender, receiver)
		{
		}

		MessageFinish::~MessageFinish()
		{
		}

		DWORD MessageFinish::MessageId() const
		{
			return MessageID;
		}
	}
}
