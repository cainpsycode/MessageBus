#pragma once
#include <string>
#include "../MessageBus/IMessage.h"

using namespace std;
using namespace MessageBus;

namespace Test
{
	namespace Messages
	{
		class MessageStart : public IMessage
		{
		public:
			MessageStart(GUID sender, GUID receiver, const wstring& filePath);
			~MessageStart();
			virtual DWORD MessageId() const;
			wstring FilePath() const;

			static const DWORD MessageID = 0x00000001;
		private:
			const wstring _filePath;
		};
	}
}