#pragma once
#include "BusinessEntities\Point.h"
#include "INavigationViewersNView.h"
#include "IRegistrationErrorVisualizer.h"

class misLandmarkPointerRepresentation;

class misRegistrationErrorVisualizer :public IRegistrationErrorVisualizer
{
public:
	misRegistrationErrorVisualizer(std::shared_ptr<INavigationViewersNView> gViwer);
	void HideRegistrationErrorLandmark() override;
	void ShowRegistrationErrorLandmark() override;
	void SetFinalRegisteredPosition(parcast::Point<double, 3> val) override;
private:
	std::shared_ptr<INavigationViewersNView> m_GroupViewer;
	std::shared_ptr<misLandmarkPointerRepresentation> m_RegisterdPointSeedRep;
	parcast::Point<double, 3> m_finalRegisteredPosition;
};