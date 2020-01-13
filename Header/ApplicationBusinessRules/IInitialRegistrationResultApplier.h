#pragma once

class ICoordinateSystemRenderer;

namespace parcast
{
	class IInitialRegistrationResultApplier
	{

	public:
		virtual ~IInitialRegistrationResultApplier() = default;
		virtual void ApplyRegistration(std::string const& referenceUid, std::string const& imageUid) = 0;
		virtual bool  IsRegistrationExist(std::string const& referenceUid, std::string const& imageUid) const = 0;
	};
}