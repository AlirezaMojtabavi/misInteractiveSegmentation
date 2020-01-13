#pragma once
#include "IImplantSource.h"
MOCK_BASE_CLASS(MockImplantSource, IImplantSource)
{
	MOCK_NON_CONST_METHOD(SetEntry, 1, void(const parcast::PointD3& point));
	MOCK_CONST_METHOD(GetEntry, 0, parcast::PointD3());
	MOCK_NON_CONST_METHOD(SetTarget, 1, void(const parcast::PointD3& point));
	MOCK_CONST_METHOD(GetTarget, 0, parcast::PointD3());
	MOCK_NON_CONST_METHOD(SetRadius, 1, void(double radius));
	MOCK_CONST_METHOD(GetRadius, 0, double());
	MOCK_NON_CONST_METHOD(SetTargetRadius, 1, void(double radius));
	MOCK_CONST_METHOD(GetMapper, 0, vtkSmartPointer<vtkMapper>());
};
