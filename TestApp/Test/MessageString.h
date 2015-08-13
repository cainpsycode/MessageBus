#pragma once
#include <string>
#include "../MessageBus/IMessage.h"

using namespace std;
using namespace MessageBus;

namespace Test
{
	namespace Messages
	{
		class MessageString : public IMessage
		{
		public:
			MessageString(GUID sender, GUID receiver, const wstring& fileString);
			~MessageString();
			virtual DWORD MessageId() const;
			wstring FileString() const;

			static const DWORD MessageID = 0x00000003;
		private:
			const wstring _fileString;
		};
	}
}