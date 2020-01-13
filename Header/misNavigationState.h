#pragma once

#include "misDejitterizedValue.h"
#include "misMathUtils.h"
#include "misObject.h"

// The misNavigationState class holds current navigation state information that includes planned points and current tool position
// and orientation. An object of this class must be created and regularly updated by clients of navigation spatial objects. The
// object is passed to navigation spatial object which in turn will use this information to update the displayed navigation guides.
// The navigations state comprises of a pair of fixed planned points (start and end) and a tool space configuration (tip and 
// orientation). The aim of navigation is to position the too tip on the plan end and orientate the tool along the axis joining
// plan start to plan end.
class misNavigationState : public misObject
{
	misObjectMacro(misNavigationState, misObject);
	misObjectNewMacro(misNavigationState);

	// Get/Set planned starting point in Cartesian world coordinates 
	virtual const double *GetPlanStartPoint() const;
	virtual void SetPlanStartPoint(double *startPoint);

	// Gets/sets planned ending point in Cartesian world coordinates 
	virtual const double *GetPlanEndPoint() const;
	virtual void SetPlanEndPoint(double *endPoint);

	// Gets/sets current normalized orientation vector of the tool, e.g., (0, 1, 0) when the tool is oriented along the Y axis.
	virtual const double *GetToolNormalDirection() const;
	virtual void SetToolNormalDirection(double normalDirection[3]);

	// Gets/sets current position of the tool tip.
	virtual const double *GetToolTipPosition() const;
	virtual void SetToolTipPosition(double *position);

	// Calculates normalized direction of the planned points by subtracting the start point from end point (dir = end - start) and 
	// performing a normalization. 
	void CalculatePlanNormalDirection(double direction[3]);

	// Calculates the length of the plan, i.e., | start - end |
	double CalculatePlanLength();

	// It calculates the projection of the tool tip position on the plan axis and stores it in the given parameter. It is used for
	// plan axis depth and distance navigation.
	inline void CalculateToolTipProjectionOnPlanAxis(double projectedPoint[3])
	{
		misMathUtils::ProjectPointOnLine(m_PlanStartPoint, m_PlanEndPoint, m_ToolTipPosition, projectedPoint);
	}

	// Determines whether the navigation state object is initialized, that is, the planned points are set.
	virtual bool IsInitialized() const;

	virtual ~misNavigationState() {}

protected:
	misNavigationState();

private:
	// Cartesian coordinates of current position of the tool tip
	double m_ToolTipPosition[3];
	misDejitterizedDouble m_DejitterizedToolTipPosition[3];

	// Normalized orientation vector of the tool such as (0, 1, 0) when the tool is oriented along the Y axis
	double m_NormalToolOrientation[3];
	misDejitterizedDouble m_DejitterizedNormalToolOrientation[3];

	// Cartesian coordinates of the starting point of the planned arrow in wold coordinates
	double m_PlanStartPoint[3];

	// Cartesian coordinates of the ending point of the planned arrow in wold coordinates
	double m_PlanEndPoint[3];

	bool m_IsPlanEndPointSet;	// Whether the plan start point is set - part of initialization
	bool m_IsPlanStartPointSet;	// Whether the plan end point is set - part of initialization
	bool m_IsToolTipPositionSet;	// Whether the tool tip position is set - part of initialization
	bool m_IsToolOrientationSet;	// Whether the tool orientation is set - part of initialization

};

