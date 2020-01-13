#pragma once
#include "misSequenceManager.h"
#include "INavigationViewersNView.h"
#include "IPlanNavigationVisualizer.h"
#include "IPositionInPlanCoordinateSystemCalculatorSetter.h"
#include "IPilotIndicatorColorSpecifier.h"
#include "INavigationTrackingHelper.h"
#include "CustomizeArcTan.h"
#include "IViewerRepository.h"
#include "IGroupViewerFactory.h"
#include "misSpineNavigationSubSequence.h"


using namespace parcast;

class misSpineNavigationSequence : public misSequenceManager
{
public:

	misSpineNavigationSequence(
		std::shared_ptr<ICoordinateSystemCorrelationManager<std::string>> correlationManager,
		std::shared_ptr<IGroupViewerFactory> groupFactory, 
		std::shared_ptr<IViewerFactory>,
		std::shared_ptr<IViewerRepository> viwerRepo,
		misStrctTabModel tabModel,
		std::shared_ptr<IPositionInPlanCoordinateSystemCalculatorSetter> positionInPlanCoordinateSystemCalculator,
		std::shared_ptr<IPlanNavigationVisualizer> planNavigationVisualizer,
		std::shared_ptr<IPilotIndicatorColorSpecifier> pilotIndicatorsColorSpecifier, 
		std::shared_ptr<INavigationTrackingHelper> trackingHelper, 
		CustomizeArcTan expFunction,
		std::shared_ptr<IPilotIndicatorColorSpecifier> crossIndicatorColorSpecifier,
		std::shared_ptr<IPilotIndicatorColorSpecifier> circleIndicatorColorSpecifier,
		std::shared_ptr<IPilotIndicatorColorSpecifier> depthIndicatorColorSpecifier, std::shared_ptr<misSoftwareInformation> softwareInformation);
	~misSpineNavigationSequence() = default;

	std::shared_ptr<misSpineNavigationSubSequence> GetNavigationManager() const;;
	virtual bool ProcessRequest(misGUIEvent* pEvent);
	misGUIEventConvertor* GetGuiConvertorList();

protected:
	std::shared_ptr<misSpineNavigationSubSequence> m_NavigationSubSequence;
	std::shared_ptr<ISimpleDataPackage> m_CurrentPackage;
	std::shared_ptr<INavigationViewersNView> m_GroupViewer;

};