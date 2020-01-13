#pragma once

#include "misNavigationGuideObject.h"

// The misPlanDepthNavigationGuideObject class provides a navigation guide in the form of an indicator on a corner of the stage
// view to inform the clinician of the current vertical position of the tool tip (with regard to the depth of the plan). The guide 
// is composed of three bars placed on top of one another.
// The top bar is a variable height bar of color colour1. Height of the top bar is logarithmically proportional to the distance 
// (along the plan axis) of the tool tip to the plan start (entry) if the tool tip projection on the plan axis is outside the range
// between plan points and at the same time nearer to the start point than the end point. If the tool tip is not in such a position,
// height of the top bar is zero. We call this the pre-entry indicator. It gives the surgeon a qualitative measure of how far the 
// tool must travel in the direction of the plan axis to meet the entry point.
// The bottom bar is a variable height bar of color colour2. Height of the bottom bar is logarithmically proportional to the 
// distance (along the plan axis) of the tool tip to the plan end (exit) point if the tool tip projection on the plan axis is 
// outside the range between plan points and at the same time nearer to the end point than the start point. If the tool tip is not 
// in such a position, height of the bottom bar is zero. We call this the post-exit indicator. It gives the surgeon a qualitative 
// measure of how far, in the direction of the plan axis, the tool has gone beyond the plan end point.
// The middle bar has a fixed height and is composed of an upper and a lower part of different colours (respectively colour1 and 
// colour2) and variable relative heights. When the pre-entry bar height is non-zero, the lower part of the middle bar takes 
// completely over and the middle bar is painted completely in colour1. When the post-exit bar height is non-zero, the upper part
// of the middle bar takes over and the middle bar is painted completely in colour2. In the case where both pre-entry and post-exit
// indicators are zero (the tool tip projection point is within the range of the planned points), the relative height of 
// the upper part is the ratio of the distance (along the plan axis) between the tool tip to the plan start point, and the total
// plan length. We shall call this the intra-plan indicator. It gives the surgon a qualitative measure of how much progress the 
// tool has made into the plan.
// In general the aim of drilling is to have a solid intra-plan bar painted in Colour1 with the pre-entry bar completely absent and
// the post-exit bar nonexistent or kept to a minimum. The red (lower) part of the intra-plan bar may also not vanish completely.
class misPlanDepthNavigationGuideObject : public misNavigationGuideObject
{
	misObjectMacro(misPlanDepthNavigationGuideObject, misNavigationGuideObject);
	misObjectNewMacro(misPlanDepthNavigationGuideObject);

public:
	~misPlanDepthNavigationGuideObject(void);

	// Overrides abstract base. It calculates the projected position of the tool tip on the plan axis, and based on that, determines
	// the represented state of the three indicator bars.
	virtual void UpdateRepresentation();

	// Gets/sets Colour1. This colour is used to indicate the distance before the plan start point is reached (the pre-entry bar)
	// and the distance advanced into the plan (upper part of intra-plan bar). 
	misPrivate3VectorVariableWithPublicAccessorsMacro(double, m_Colour1, Colour1);

	// Gets/sets Colour2. This colour is used to indicate the remaining distance plan end point is reached (the intra-plan bar) 
	// after the tool enters the planned area and also the distance traveled out of the planned area, past the plan end point
	// (post-exit bar). 
	misPrivate3VectorVariableWithPublicAccessorsMacro(double, m_Colour2, Colour2);

	// Sets/gets the maximum distance from the entry point that the pre-entry indicator bar can display. Any value greater than
	// this simply does not alter the bar height.
	misPrivateVariableWithPublicAccessorsMacro(double, m_PreEntryMaxDistance, PreEntryMaxDistance);

	// Sets/gets the maximum distance from the exit point that the post-exit indicator bar can display. Any value greater than
	// this simply does not alter the bar height.
	misPrivateVariableWithPublicAccessorsMacro(double, m_PostExitMaxDistance, PostExitMaxDistance);

	// Sets/gets the default/maximum height, in world coordinates scale, for each of the three indicator bars.
	misPrivateVariableWithPublicAccessorsMacro(double, m_MaximumBarHeight, MaximumBarHeight);

	// Sets/gets the default width, in world coordinates scale, for each of the three indicator bars.
	misPrivateVariableWithPublicAccessorsMacro(double, m_BarWidth, BarWidth);

	// Amount of padding, in world coordinates scale, placed between each pair of adjacent bars on top of each other.
	misPrivateVariableWithPublicAccessorsMacro(double, m_Padding, Padding);

protected:
	// The PositionStatus enumeration gives has distinct values that determine the position status of the tool tip with respect to 
	// the plan. The position can have three statuses each of which should be treated differently as representation is concerned.
	enum PositionStatus
	{
		PS_PreEntry,
		PS_IntraPlan,
		PS_PostExit,
		PS_Unknown
	};

	// The AnalyzedPositionParameters struct holds parameters after an analysis if performed on the projected position of the tool
	// tip on the plan axis and its position relative to plan start and end points.
	struct AnalyzedPositionParameters
	{
		AnalyzedPositionParameters()
			: positionStatus(PS_Unknown), distanceFromStart(0), distanceFromEnd(0), intraPlanProgress(0) {}

		PositionStatus positionStatus;	// Position status of the projected point with respect to the planned points.
		double distanceFromStart;	// Distance of the projected point from the plan start point.
		double distanceFromEnd;	// Distance of the projected point from the plan end point.
		
		// The amount of progress of the tool made into the plan. This is 0 if positionStatus is PS_PreEntry, 1 if it is 
		// PS_PostExit, and a value between if positionStatus is PS_IntraPlan.
		double intraPlanProgress;	
	};

	// This struct holds parameters required to updated the representation of the object. The height parameters are computed using
	// the MaximumBarHeight property.
	struct RepresentationParameters
	{
		RepresentationParameters () 
			: preEntryBarHeight(0), intraPlanUpperBarHeight(0), intraPlanLowerBarHeight(0), postExitBarHeight(0) {}

		double preEntryBarHeight;
		double intraPlanUpperBarHeight;
		double intraPlanLowerBarHeight;
		double postExitBarHeight;
	};

	// Creates and initializes the navigation guide spatial object. It creates, initializes and adds the indicator bars to the list 
	// of props and sets the default settings.
	misPlanDepthNavigationGuideObject(void);

	// Analyzes projected position of the tool tip on the plan axis with respect to plan start and end points and returns 
	// analysis results as a series of parameters such as distance of the projected point from start and end point and the amount
	// of progress made into the planned zone (0 if in PreEntry and 1 if in PostExit). Its return value determines the current
	// position status of the projected point with respect to the planned points.
	AnalyzedPositionParameters AnalyzeRelativeToolPosition();

	// Computes the heights of the four indicator bars based on the given position parameters. The computed representation 
	// parameters can be directly used to modify the plane sources for each of the bars.
	RepresentationParameters ComputeRepresentationParameters(const AnalyzedPositionParameters &positionParameters);

	// Initializes the given plane source, creates a 2d mapper and a 2d actor, and then it attaches the source to the mapper which 
	// is then passed to the actor. It then returns the created actor which can be added to list of props. Called by ctor.
	vtkSmartPointer<vtkActor2D> InitializeBarGraphicsPipeline(vtkSmartPointer<vtkPlaneSource> planeSource, double * colour);

	// During UpdateRepresentation(), representation of each bar is individually updated by updating its corresponding plane source
	// based on corresponding computed representation parameters. UpdatePlaneSource does this by setting the plane referenced by 
	// planeSource to a new plane positioned at (m_BarPosition[0], m_BarPosition[0] + positionY) with dimensions 
	// (m_BarWidth, height).
	void UpdatePlaneSource(vtkSmartPointer<vtkPlaneSource> planeSource, double positionY, double height);

private:
	// The plane source used for creating the rectangular representation of the pre-entry bar.
	vtkSmartPointer<vtkPlaneSource> m_PreEntryBarPlaneSource;

	// The plane source used for creating the rectangular representation of the upper part of the intra-plan bar.
	vtkSmartPointer<vtkPlaneSource> m_IntraPlanIndicatorLowerBarPlaneSource;

	// The plane source used for creating the rectangular representation of the lower part of the intra-plan bar.
	vtkSmartPointer<vtkPlaneSource> m_IntraPlanIndicatorUpperBarPlaneSource;

	// The plane source used for creating the rectangular representation of the post-exit bar.
	vtkSmartPointer<vtkPlaneSource> m_PostExitBarPlaneSource;

	// Position of the bottom left corner of the lower part of the intra-plan bar in world coordinates.
	double m_BarPosition [2];
};

