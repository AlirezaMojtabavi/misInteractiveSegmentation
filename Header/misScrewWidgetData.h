#pragma once

#include "misEvent.h"
#include "misSimplePointType.h"
#include "misStringTools.h"
#include "misVertebraEnum.h"
 
// The misScrewWidgetUpdate define screw or implant data
class misScrewWidgetData
{

public:
	misScrewWidgetData();
	
	// Transform start and end point of plan data with provided matrix
	void TransformPlan(vtkSmartPointer<vtkTransform> transfom);
	void Reset();

	misSimplePointType GetStartPoint() const;
	void SetStartPoint(misSimplePointType val);
	void SetStartPoint(double const* point);
	misSimplePointType GetEndPoint() const;
	void SetEndPoint(misSimplePointType val);
	void SetEndPoint(double const* val);
	
	// The matrix represent the transformation of current screw corner(3 X orthogonal axis)
	vtkSmartPointer<vtkMatrix4x4> GetTransformMatrix() const;

	// Oly update current transform of  of misScrewWidgetData
	void DeepCopyTransformMatrix(vtkSmartPointer<vtkMatrix4x4> val);
	
	ScrewWidgetSourceType GetSourceType() const;
	void SetSourceType(ScrewWidgetSourceType val);
	ScrewWidgetInteractionType GetInterationType() const;
	void SetInterationType(ScrewWidgetInteractionType val);
	misUID GetScrewUID() const;
	void SetScrewUID(misUID val);
	double GetScrewDiameter() const;
	void SetScrewDiameter(double val);
	double GetTargetRadius() const;
	void SetTargetRadius(double val);
	void SetStartPointModified();
	void SetEndPointModified();
	bool IsStartPointModified() const;
	bool IsEndPointModified() const;
private:

	misSimplePointType	m_StartPoint;
	misSimplePointType	m_EndPoint;
	bool m_StartPointModified = false;
	bool m_EndPointModified = false;

	double screwDiameter;
	misUID	m_ScrewUID;
	ScrewWidgetSourceType	m_sourceType;
	vtkSmartPointer<vtkMatrix4x4> m_TransformMatrix;
	ScrewWidgetInteractionType m_interationType;
	double m_TargetRadius = 1.0;

};

#pragma warning ( suppress : 4800)	// IGSTK crap
igstkLoadedEventMacro(misScrewWidgetUpdateEvent, misEvent, misScrewWidgetData);