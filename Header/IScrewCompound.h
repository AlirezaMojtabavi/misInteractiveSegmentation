#pragma once

#include "misScrewWidgetData.h"
#include "BusinessEntities\Point.h"
#include "VisualizationGeneralTypes.h"

class misPlanWidget;

class IScrewCompound
{
public:

	typedef itk::Vector<double, 3> VectorType;
	virtual void	SetRotationStateValues() = 0;
	virtual void	SetExtendStateValues(double maxLineLen) = 0;
	virtual void	SetPositionStateValue() = 0;
	virtual void	SetFreeStateValue() = 0;
	virtual void	SetScrewWidget(misScrewWidgetData screwWidgetNewVal) = 0;
	virtual double* GetPoint1WorldPosition()  const = 0;
	virtual double* GetPoint2WorldPosition() const = 0;
	virtual ScrewWidgetInteractionType GetInteractionType() const = 0;
	virtual vtkMatrix4x4*	GetTransformMatrix() const = 0;
	virtual misPlanWidget* GetWidget() const = 0;
	virtual void SetInteractor(vtkRenderWindowInteractor*	pRenderWindowInteractor) = 0;
	virtual void	Off() = 0;
	virtual void	On() = 0;
	virtual void	SetColor(misColorStruct screwColor) = 0;
	virtual void SetWidth(const double& width) = 0;
	virtual void	SetLocked(bool finalized) = 0;
	virtual misUID	GetScrewUID() const= 0;
	virtual void	HighlightScrew(bool highlight) = 0;
	virtual void	SetSelected(bool selected) = 0;
	virtual bool	GetSelected() const = 0;
	virtual void SetTargetRadius(double val) = 0;
	virtual void SetEntry(parcast::PointD3 point) = 0;
	virtual void SetTarget(parcast::PointD3 point) = 0;

	
	~IScrewCompound(){}
};
