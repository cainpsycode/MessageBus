#pragma once
#include <string>
#include "../MessageBus/IMessage.h"

using namespace std;
using namespace MessageBus;

namespace Test
{
	namespace Messages
	{
		class MessageFinish : public IMessage
		{
		public:
			MessageFinish(GUID sender, GUID receiver);
			~MessageFinish();
			virtual DWORD MessageId() const;

			static const DWORD MessageID = 0x00000004;
		};
	}
}