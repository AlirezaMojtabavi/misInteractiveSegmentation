#pragma once

#include "IParametricSpline.h"

MOCK_BASE_CLASS(MockParametricSpline, IParametricSpline)
{
	
	MOCK_CONST_METHOD(GetVTKParametricSpline, 0, vtkSmartPointer<vtkParametricSpline>());
	MOCK_CONST_METHOD(EvaluateAt, 1, PointType (double splineParameter));
	MOCK_CONST_METHOD(GetLength, 0, double());
 	MOCK_CONST_METHOD(GetPartialLength, 2, double(double minVal, double maxVal));
 	MOCK_CONST_METHOD(GetSplineParamByPartialLength, 2, double (double Length, double minVal), identifier_1 );
 	MOCK_CONST_METHOD(GetSplineParamByPartialLength, 1, double (double length), identifier_2 );
 	MOCK_CONST_METHOD(ComputeNormalVecAt, 1, VectorType (double splineParam));
 	MOCK_CONST_METHOD(GetDisplacedSpline, 1, std::shared_ptr<IParametricSpline>(double displacementSize));
 	MOCK_CONST_METHOD(GetMinParameter, 0, double());
 	MOCK_CONST_METHOD(GetMaxParameter, 0, double());
 	MOCK_CONST_METHOD(GetPoints, 1, std::vector<PointType>(int pointsNum));
};