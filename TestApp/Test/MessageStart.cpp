#include "MessageStart.h"
#include <tchar.h>

namespace Test
{
	namespace Messages
	{
		MessageStart::MessageStart(GUID sender, GUID receiver, const wstring& filePath) 
			: IMessage(sender, receiver),
			_filePath(filePath)
		{
		}

		MessageStart::~MessageStart()
		{
		}

		DWORD MessageStart::MessageId() const
		{
			return MessageID;
		}

		wstring MessageStart::FilePath() const
		{
			return _filePath;
		}
	}
}
