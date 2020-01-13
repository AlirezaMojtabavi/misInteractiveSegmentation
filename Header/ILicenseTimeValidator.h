#pragma once
namespace parcast
{
	enum LicenceTimeState
	{
		TIMEEXPIRED,
		TIMEVALID,
		DONGLEERROR
	};

	class ILicenseTimeValidator
	{
	public:
		virtual ~ILicenseTimeValidator() = default;
		virtual LicenceTimeState CheckValidity() = 0;
	};
}
