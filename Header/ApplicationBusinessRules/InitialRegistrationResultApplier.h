#pragma once

#include "IInitialRegistrationResultApplier.h"

class ILandmarkRegistrationCalculator;

namespace parcast
{
	class ITransformFactory;

	class InitialRegistrationResultApplier : public IInitialRegistrationResultApplier
	{
	public:
		using ICorrelationManager_string = ICoordinateSystemCorrelationManager<std::string>;

		InitialRegistrationResultApplier(
			std::shared_ptr<ICorrelationManager_string> correlationManager,
			std::shared_ptr<ILandmarkRegistrationCalculator> registrationCalculator,
			std::shared_ptr<ITransformFactory> transformFactory, const int minimumRequiredPointsForPointBasedRegn);

		void ApplyRegistration(std::string const& referenceUid, std::string const& imageUid) override;

		bool  IsRegistrationExist(std::string const& referenceUid, std::string const& imageUid)  const override;

	private:
		std::shared_ptr<ICorrelationManager_string> m_CorrelationManager{} ;
		std::shared_ptr<ILandmarkRegistrationCalculator> m_RegistrationCalculator{} ;
		std::shared_ptr<ITransformFactory> m_TransformFactory{} ;
		const int MinimumRequiredPointsForPointBasedRegistration;
	};
}
