#pragma once
#include "IDonglePasswordDecryptor.h"




namespace  parcast
{
	class DonglePasswordDecryptor : public IDonglePasswordDecryptor
	{
	public:
		std::vector<std::string> DecryptPasswords();
	private:
		std::string DecryptString(const char *instr, const char *passPhrase) const;
	};
}
