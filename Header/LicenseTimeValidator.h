#pragma once
#include "ILicenseTimeValidator.h"
#include <Ry4S.h>

namespace parcast
{
	class LicenseTimeValidator : public ILicenseTimeValidator
	{
	public:
		LicenceTimeState CheckValidity() override;
		static unsigned long LicenseTimeValidator::StringToWord(std::string password);
		SYSTEMTIME GetLicenseRemaining();


	private:
		bool Initialize();
		LicenceTimeState CheckValidPeriod();
		DWORD m_LongParameter1 = 0;
		DWORD m_LongParameter2 = 0;
		WORD  m_Parameter1 = 0;
		WORD  m_Parameter2 = 0;
		WORD  m_Parameter3 = 0;
		WORD  m_Parameter4 = 0;
		BYTE m_Buffer[1024] = { "0" };
		WORD m_Handel[16];
		DWORD m_ReturnValue = 0;
		SYSTEMTIME m_LicenseRemainingTime;

	};
}