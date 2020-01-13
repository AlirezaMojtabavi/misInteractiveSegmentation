#pragma once
#include <IPlan.h>
#include <IPositionInPlanCoordinateSystemCalculatorGetter.h>
#include <IPilotIndicatorColorSpecifier.h>


namespace parcast
{

	class IPlanNavigationVisualizer
	{
	public:
		virtual ~IPlanNavigationVisualizer() = default;

		// Asks the underlying window object to render its display area. Must be called after the plan navigation indicator backend
		// has new position information to update the view.
		virtual void Render() = 0;

		// The following set of methods define thresholds for each of the Grey, Yellow, and Green zones. The threshold parameters 
		// define maximum values for some of the tracking tool position coordinates with respect to the plan coordinate system.
		// For the tool position to fall within any of the zones, all parameters must fall within the given thresholds.
		// The height threshold parameter is the maximum axial distance from the tool tip to the plan start point.
		// The radius threshold parameter is the maximum radial distance from the tool tip to the plan start point (in the X-Y plane).
		virtual void SetGrayZoneThreshold(double height, double radius) = 0;
		virtual void Initialize(vtkSmartPointer<vtkRenderer> renderer, bool paralleProjecton) = 0;
		virtual void SetPlan(std::weak_ptr<IPlan> plan) = 0;
		virtual void SetFreezeState(bool state) = 0;
		virtual std::shared_ptr<IPositionInPlanCoordinateSystemCalculatorGetter> GetPositionInPlanCoordinate() = 0;
		virtual IPilotIndicatorColorSpecifier::IndicatorColor GetIndicatorColor(std::string name) = 0;
	};

}

