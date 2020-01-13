#include "StdAfx.h"
#include "InitialRegistrationResultApplier.h"

#include "ITransformFactory.h"
#include "ICoordinateSystemRenderer.h"
#include "ILandmarkRegistrationCalculator.h"
#include "misRegistrationStrcts.h"

using namespace parcast;

InitialRegistrationResultApplier::InitialRegistrationResultApplier(
	std::shared_ptr<ICorrelationManager_string> correlationManager,
	std::shared_ptr<ILandmarkRegistrationCalculator> registrationCalculator,
	std::shared_ptr<ITransformFactory> transformFactory, 
	const int minimumRequiredPointsForPointBasedReg):
	m_CorrelationManager(correlationManager),
	m_RegistrationCalculator(registrationCalculator),
	m_TransformFactory(transformFactory), 
	MinimumRequiredPointsForPointBasedRegistration(minimumRequiredPointsForPointBasedReg)
{
}

bool InitialRegistrationResultApplier::IsRegistrationExist(std::string const& referenceUid, std::string const& imageUid) const
{
	auto const regResult = m_RegistrationCalculator->GetRegistrationResult();
	return (regResult.regState == SuccessRegistration &&
		regResult.NumOfValidLandmarks >= MinimumRequiredPointsForPointBasedRegistration);
}


void InitialRegistrationResultApplier::ApplyRegistration(std::string const& referenceUid, std::string const& imageUid)
{
	if (!IsRegistrationExist(referenceUid, imageUid))
		return;

	double transMat[16];
	m_RegistrationCalculator->GetRegistrationMatrix(transMat);
	auto const trans = m_TransformFactory->Create(transMat);
	m_CorrelationManager->SetTransform(referenceUid, imageUid, trans);
}
