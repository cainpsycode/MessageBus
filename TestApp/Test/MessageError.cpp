#include "MessageError.h"
#include <tchar.h>

namespace Test
{
	namespace Messages
	{
		MessageError::MessageError(GUID sender, GUID receiver, const wstring& errorDescription)
			: IMessage(sender, receiver),
			_errorDescription(errorDescription)
		{
		}

		MessageError::~MessageError()
		{
		}

		DWORD MessageError::MessageId() const
		{
			return MessageID;
		}

		wstring MessageError::ErrorDescription() const
		{
			return _errorDescription;
		}
	}
}
