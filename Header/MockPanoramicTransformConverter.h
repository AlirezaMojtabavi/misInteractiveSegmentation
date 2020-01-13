#pragma once

#include <turtle/mock.hpp>

#include "IPanoramicTransformConverter.h"

MOCK_BASE_CLASS(MockPanoramicTransformConverter, IPanoramicTransformConverter)
{
	MOCK_NON_CONST_METHOD(SetXYSplineCurve, 1, void (vtkSmartPointer<vtkParametricSpline> spline));
	MOCK_NON_CONST_METHOD(SetTransformInImageSpace, 1, void (std::shared_ptr<ITransform> objectTransform));
	MOCK_CONST_METHOD(GetTransformInPanoramicSpace, 0, std::shared_ptr<ITransform> ());
	virtual void SetTransformInPanoramicSpace( std::shared_ptr<const ITransform> objectTransform );
	virtual std::shared_ptr<ITransform> GetTransformInImageSpace() const;
};