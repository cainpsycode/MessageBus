#include "MessageString.h"
#include <tchar.h>

namespace Test
{
	namespace Messages
	{
		MessageString::MessageString(GUID sender, GUID receiver, const wstring& fileString)
			: IMessage(sender, receiver),
			_fileString(fileString)
		{
		}

		MessageString::~MessageString()
		{
		}

		DWORD MessageString::MessageId() const
		{
			return MessageID;
		}

		wstring MessageString::FileString() const
		{
			return _fileString;
		}
	}
}
