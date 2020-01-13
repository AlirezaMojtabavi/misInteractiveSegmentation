#include "StdAfx.h"
#include "misPlanDepthNavigationGuideObject.h"

#include "misMathUtils.h"

misPlanDepthNavigationGuideObject::misPlanDepthNavigationGuideObject(void)
{
	SetMaximumBarHeight(100);
	SetBarWidth(30);
	SetPadding(3);
	SetPreEntryMaxDistance(300);
	SetPostExitMaxDistance(200);
	SetColour1(.1, .9, .2);
	SetColour2(.9, .2, .1);

	m_BarPosition[0] = 30;
	m_BarPosition[1] = 100 + m_MaximumBarHeight;

	m_PreEntryBarPlaneSource = vtkSmartPointer<vtkPlaneSource>::New();
	vtkSmartPointer<vtkActor2D> preEntryBarActor = InitializeBarGraphicsPipeline(m_PreEntryBarPlaneSource, m_Colour1);

	m_IntraPlanIndicatorUpperBarPlaneSource = vtkSmartPointer<vtkPlaneSource>::New();
	vtkSmartPointer<vtkActor2D> intraPlanUpperBarActor = 
		InitializeBarGraphicsPipeline(m_IntraPlanIndicatorUpperBarPlaneSource, m_Colour1);

	m_IntraPlanIndicatorLowerBarPlaneSource = vtkSmartPointer<vtkPlaneSource>::New();
	vtkSmartPointer<vtkActor2D> intraPlanLowerBar = 
		InitializeBarGraphicsPipeline(m_IntraPlanIndicatorLowerBarPlaneSource, m_Colour2);

	m_PostExitBarPlaneSource = vtkSmartPointer<vtkPlaneSource>::New();
	vtkSmartPointer<vtkActor2D> postExitBarActor = InitializeBarGraphicsPipeline(m_PostExitBarPlaneSource, m_Colour2);

	AddProp(preEntryBarActor);
	AddProp(intraPlanUpperBarActor);
	AddProp(intraPlanLowerBar);
	AddProp(postExitBarActor);
}

misPlanDepthNavigationGuideObject::~misPlanDepthNavigationGuideObject(void)
{
}

void misPlanDepthNavigationGuideObject::UpdateRepresentation()
{
	AnalyzedPositionParameters posParams = AnalyzeRelativeToolPosition();
	RepresentationParameters repParam = ComputeRepresentationParameters(posParams);

	UpdatePlaneSource(m_PreEntryBarPlaneSource, m_MaximumBarHeight + m_Padding, repParam.preEntryBarHeight);
	UpdatePlaneSource(m_IntraPlanIndicatorUpperBarPlaneSource, repParam.intraPlanLowerBarHeight, repParam.intraPlanUpperBarHeight);
	UpdatePlaneSource(m_IntraPlanIndicatorLowerBarPlaneSource, 0, repParam.intraPlanLowerBarHeight);
	UpdatePlaneSource(m_PostExitBarPlaneSource, -repParam.postExitBarHeight - m_Padding, repParam.postExitBarHeight);
}

misPlanDepthNavigationGuideObject::AnalyzedPositionParameters misPlanDepthNavigationGuideObject::AnalyzeRelativeToolPosition()
{
	// The tool tip can be in either one of the positions that define the state of all three indicators:
	// 1. Outside the plan range, nearer to the start point.
	// 2. Inside the plan range.
	// 3. Outside the plan range, nearer to the end point.
	// We determine which of the above cases is true through the following computation:
	// Let L be the length of the plan, that is the distance between the plan start point and the plan end point; and let Ds be
	// the distance between the projected position of the tool tip on the axis and the plan start point; and let De be the 
	// distance between the projected position of the tool tip on the axis and the plan end point. Now let D = De - Ds only for
	// convenience in computation.
	// Case 1 is true if: De - Ds = +L			or	D = +L
	// Case 2 is true if: -L < De - Ds < +L		or	-L < D < +L
	// Case 3 is true if: De - Ds = -L			or	D = -L
	// But since we are dealing with "double" data type, we cannot check for exact equality, and for case 1 and case 3 we work out 
	// different, but equivalent rules:
	// Case 1 is true if: De > Ds && De > L		or D > 0 && De > L
	// Case 3 is true if: De < Ds && Ds > L		or D > 0 && De > L
	// Case 2 is true if none of the above holds.

	AnalyzedPositionParameters parameters;

	if (!GetNavigationState()->IsInitialized())
		return parameters;

	double planLength = GetNavigationState()->CalculatePlanLength();	// L
	const double *planStartPoint = GetNavigationState()->GetPlanStartPoint();
	const double *planEndPoint = GetNavigationState()->GetPlanEndPoint();
	
	double projectionOnTheAxis[3];
	GetNavigationState()->CalculateToolTipProjectionOnPlanAxis(projectionOnTheAxis);

	parameters.distanceFromStart = std::sqrt(vtkMath::Distance2BetweenPoints(projectionOnTheAxis, planStartPoint));	// Ds
	parameters.distanceFromEnd = std::sqrt(vtkMath::Distance2BetweenPoints(projectionOnTheAxis, planEndPoint));	// De

	double distanceDelta = parameters.distanceFromEnd - parameters.distanceFromStart;	// D = De - Ds
	if (parameters.distanceFromEnd > parameters.distanceFromStart && parameters.distanceFromEnd > planLength)	// case 1
	{
		parameters.positionStatus = PS_PreEntry;
		parameters.intraPlanProgress = 0;
	}
	else if (parameters.distanceFromEnd < parameters.distanceFromStart && parameters.distanceFromStart > planLength)	// case 3
	{
		parameters.positionStatus = PS_PostExit;
		parameters.intraPlanProgress = 1;
	}
	else	// case 2 of course
	{
		parameters.positionStatus = PS_IntraPlan;
		parameters.intraPlanProgress = parameters.distanceFromStart / planLength;	
	}

	return parameters;
}

misPlanDepthNavigationGuideObject::RepresentationParameters misPlanDepthNavigationGuideObject::ComputeRepresentationParameters(
	const AnalyzedPositionParameters &positionParameters)
{
	RepresentationParameters repParams;

	switch (positionParameters.positionStatus)
	{
	case PS_PreEntry:
		repParams.preEntryBarHeight = 
			misMathUtils::ClipValue(std::log(positionParameters.distanceFromStart) / std::log(m_PreEntryMaxDistance), 0.0, 1.0) * 
			m_MaximumBarHeight;
		repParams.intraPlanUpperBarHeight = 0;
		repParams.intraPlanLowerBarHeight = m_MaximumBarHeight;
		repParams.postExitBarHeight = 0;
		break;
	case PS_IntraPlan:
		repParams.preEntryBarHeight = 0;
		repParams.intraPlanUpperBarHeight = positionParameters.intraPlanProgress * m_MaximumBarHeight;
		repParams.intraPlanLowerBarHeight = (1 - positionParameters.intraPlanProgress) * m_MaximumBarHeight;
		repParams.postExitBarHeight = 0;
		break;
	case PS_PostExit:
		repParams.preEntryBarHeight = 0;
		repParams.intraPlanUpperBarHeight = m_MaximumBarHeight;
		repParams.intraPlanLowerBarHeight = 0;
		repParams.postExitBarHeight = 
			 misMathUtils::ClipValue(std::log(positionParameters.distanceFromEnd) / std::log(m_PostExitMaxDistance), 0.0, 1.0) * 
			 m_MaximumBarHeight;
		break;
	case PS_Unknown:
		break;
	}
	return repParams;
}

vtkSmartPointer<vtkActor2D> misPlanDepthNavigationGuideObject::InitializeBarGraphicsPipeline(
	vtkSmartPointer<vtkPlaneSource> planeSource, double * colour)
{
	vtkSmartPointer<vtkPolyDataMapper2D> quadMapper = vtkSmartPointer<vtkPolyDataMapper2D>::New();
	quadMapper->SetInputData(planeSource->GetOutput());
	vtkSmartPointer<vtkActor2D> actor = vtkSmartPointer<vtkActor2D>::New();
	actor->SetMapper(quadMapper);
	actor->GetProperty()->SetColor(colour);
	return actor;
}

void misPlanDepthNavigationGuideObject::UpdatePlaneSource(
	vtkSmartPointer<vtkPlaneSource> planeSource, double positionY, double height)
{
	planeSource->SetOrigin(m_BarPosition[0], m_BarPosition[1] + positionY, 0);
	planeSource->SetPoint1(m_BarPosition[0], m_BarPosition[1] + positionY + height, 0);
	planeSource->SetPoint2(m_BarPosition[0] + m_BarWidth, m_BarPosition[1] + positionY, 0);
}
