#pragma once

#include "misSequenceManager.h"
#include "IPlanNavigationVisualizer.h"
#include "IPositionInPlanCoordinateSystemCalculatorSetter.h"
#include "IPilotIndicatorColorSpecifier.h"
#include "CustomizeArcTan.h"

class misDentalNavigationSubSequence;
class IViewerFactory;
class IGroupViewerFactory;

using namespace parcast;

class misDentalNavigationSequence : public misSequenceManager
{
public:

	misDentalNavigationSequence(std::shared_ptr< ICoordinateSystemCorrelationManager<std::string> >
		correlationManager, std::shared_ptr<IGroupViewerFactory> groupFactory,
		std::shared_ptr<IViewerFactory> viwerFactory, misStrctTabModel tabModel,
		std::shared_ptr<IPositionInPlanCoordinateSystemCalculatorSetter> positionInPlanCoordinateSystemCalculator,
		std::shared_ptr<IPlanNavigationVisualizer> planNavigationVisualizer,
		CustomizeArcTan expFunction,
		std::shared_ptr<IPilotIndicatorColorSpecifier> crossIndicatorColorSpecifier,
		std::shared_ptr<IPilotIndicatorColorSpecifier> circleIndicatorColorSpecifier,
		std::shared_ptr<IPilotIndicatorColorSpecifier> depthIndicatorColorSpecifier);
	std::shared_ptr<misDentalNavigationSubSequence>  GetNavigationManager(void);;
	virtual bool ProcessRequest(misGUIEvent* pEvent);
	misGUIEventConvertor* GetGuiConvertorList();


protected:

	std::shared_ptr<misDentalNavigationSubSequence>  m_NavigationSubSequence;

};
