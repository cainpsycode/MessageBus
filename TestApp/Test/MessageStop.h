#pragma once
#include <string>
#include "../MessageBus/IMessage.h"

using namespace std;
using namespace MessageBus;

namespace Test
{
	namespace Messages
	{
		class MessageStop : public IMessage
		{
		public:
			MessageStop(GUID sender, GUID receiver);
			~MessageStop();
			virtual DWORD MessageId() const;

			static const int MessageID = 0x00000002;
		};
	}
}