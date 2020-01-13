#pragma once
#include "ISimpleDataPackage.h"

class ISplineVisualizer
{
public:
	using SplinePoints = std::vector<itk::Point<double, 3> >;

	virtual ~ISplineVisualizer() = default;
	virtual bool AddSplineWidgetToAxialViewer(const SplinePoints& splinePoints) = 0;
	virtual bool LockSpline() = 0;
	virtual void NewSpline() = 0;
	virtual bool UndoSpline() = 0;
	virtual void ChangeWidgetVisibility(bool visibility) = 0;
	virtual SplinePoints GetSplinePoints() = 0;
};
