#pragma once
#include "Point.h"
class ISpinousToPlanAngleMeasurment
{
public:
	virtual void SetPlan(const parcast::Point<double, 3>& start, const parcast::Point<double, 3>& end) = 0;
	virtual void SetSpinousStart(const parcast::Point<double, 3>& point) = 0;
	virtual void SetSpinousEnd(const parcast::Point<double, 3>& point) = 0;
	virtual void SetRenderWindowInteractor(vtkSmartPointer<vtkRenderWindowInteractor> interactor) = 0;
	virtual void DeleteWidget() = 0;
	virtual void SetEnable(int) = 0;
	virtual ~ISpinousToPlanAngleMeasurment() {};
};

