#pragma once
#include <vector>

namespace parcast
{
	class IDonglePasswordDecryptor
	{
	public:
		virtual std::vector<std::string> DecryptPasswords() = 0;
	};
}
