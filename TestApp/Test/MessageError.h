#pragma once
#include <string>
#include "../MessageBus/IMessage.h"

using namespace std;
using namespace MessageBus;

namespace Test
{
	namespace Messages
	{
		class MessageError : public IMessage
		{
		public:
			MessageError(GUID sender, GUID receiver, const wstring& errorDescription);
			~MessageError();
			virtual DWORD MessageId() const;
			wstring ErrorDescription() const;

			static const DWORD MessageID = 0x00000005;
		private:
			const wstring _errorDescription;
		};
	}
}