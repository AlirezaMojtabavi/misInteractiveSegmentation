#pragma once

#include "..\misIntegrationTestTools\misIntegrationNView.h"
#include "ICoordinateSystemCorrelationManager.h"
#include "misGroupViewer.h"
#include "misIntegrationTestApplication.h"
#include "misNativeWindow.h"
#include "misSpineScrewPlanningSubSeq.h"
#include "misDentalPlanningSubsequence.h"

//The class test the misScrewPlanning  subsequence
class misScrewPlaningWidgetTest : public misIntegrationNView
{
public:	
	misScrewPlaningWidgetTest(int &argc, char ** argv, int numberofView);

private:
	void ShowPackage();
	void InitiVoreenShaders();
	
	// Initialize test data for panoramic viewer
	void InitilizePanoramicView();

	void AddTestActor();

	void SetChangingContrastMode();
	void LoadTFIMap();
	void RaiseNewSplineEvent();
	void AcceptPlanEvent();

	virtual void PulseHandler() override;

	std::shared_ptr<misImage> m_Image1;
	std::shared_ptr<misSpineScrewPlanningSubSeq> m_ScrewPlanning;
	std::weak_ptr<INavigationViewersNView> m_GroupViewer;
	std::shared_ptr< ICoordinateSystemCorrelationManager<std::string> > m_CSCorrelationManager;
	vtkSmartPointer<vtkTransform> sliceTransform;
	void AddPlan();

};

