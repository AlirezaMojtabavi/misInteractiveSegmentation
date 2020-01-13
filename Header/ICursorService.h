#pragma once
#include "AxesColors.h"
#include "misEnums.h"

class ICornerProperties;
enum IMAGEORIENTATION;

class ICursorService
{
public:
	virtual void SetWidgetInteractor(vtkRenderWindowInteractor* ) = 0;
	virtual void SetRenderer(vtkRenderer* ) = 0;
	virtual void SetImageOrientation(IMAGEORIENTATION ) = 0;
	virtual void SetWidgetLineWeight(double ) = 0;
	virtual void SetWidgetType(misCursorType widgetType) = 0;
	virtual void SetWidgetBounds(double* pBounds) = 0;
	virtual void ApplyWidget(vtkProp3D* actor) = 0;
	virtual void CreateWidget(double pickingTolerance) = 0;
	virtual void EnableWidget() = 0;
	virtual void DisableWidget() = 0;
	virtual void ReleaseWidget() = 0;
	virtual void ChangeWidgetType(misCursorType ) = 0;
	virtual void AddObserver(vtkCommand* ) = 0;
	virtual void Set3DInteractionCapturedFlag(bool ) = 0;
	virtual void UpdateWidgetPosition() = 0;
	virtual void SetCornerProperties(std::shared_ptr<ICornerProperties> ) = 0;
	virtual void SetAxesColors(const parcast::AxesColors& ) = 0;
};