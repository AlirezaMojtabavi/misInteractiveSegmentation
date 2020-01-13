#pragma once
#include "IUpdateRegistrationViewWithLandMark.h"
#include "IImageToPatientLandmarkBasedRegistation.h"
#include "IViewingTypeColormapSelector.h"
#include "IRegistrationErrorVisualizer.h"

class misUpdateRegistrationViewWithLandMark :
	public IUpdateRegistrationViewWithLandMark
{
public:
	misUpdateRegistrationViewWithLandMark(std::shared_ptr<IImageToPatientLandmarkBasedRegistation> imageToReferenceRegistration, 
		std::shared_ptr<IViewingTypeColormapSelector> viewingTypeColormapSelector, std::shared_ptr<INavigationViewersNView> groupViewer,
		std::shared_ptr<IRegistrationErrorVisualizer> errorVisulizer);
	// Inherited via IUpdateRegistrationViewWithLandMark
	virtual void UpdateViewWithLandMark(int index, std::shared_ptr<ISimpleDataPackage> package, bool subTabCompleteness) override;
private:
	void SetRegistrationErrorLandmark(double finalRegisteredPosition[3]);

	std::shared_ptr<IImageToPatientLandmarkBasedRegistation> m_ImageToReferenceRegistration;
	std::shared_ptr<IViewingTypeColormapSelector> m_ViewingTypeColormapSelector;
	std::shared_ptr<INavigationViewersNView> m_GroupViewer;
	std::shared_ptr<IRegistrationErrorVisualizer> m_ErrorVisulizer;
};

