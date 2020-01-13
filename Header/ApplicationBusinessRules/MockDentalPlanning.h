#pragma once

#include "IDentalPlanning.h"

namespace parcast
{

	MOCK_BASE_CLASS(MockDentalPlanning, IDentalPlanning)
	{
		MOCK_NON_CONST_METHOD(StartUp, 0, void());
		MOCK_NON_CONST_METHOD(SetCurrentPackage, 1, void(std::shared_ptr<ISimpleDataPackage> pkg));
		MOCK_NON_CONST_METHOD(SetCurrentPlan, 1, void(std::shared_ptr<IPlan> plan));
		MOCK_NON_CONST_METHOD(CapturePoint, 1, void(const PointType& point));
		MOCK_NON_CONST_METHOD(EnableAddPlanMode, 0, void());
		MOCK_NON_CONST_METHOD(
			ModifyPlan, 3, void(std::shared_ptr<IPlan> plan, const PointType& startPoint, const PointType& endPoint));
		MOCK_NON_CONST_METHOD(NewSpline, 0, void());
		MOCK_NON_CONST_METHOD(AcceptSpline,1, void(const SplinePoints& points));
		MOCK_NON_CONST_METHOD(SetScrewDiameter, 1, void(double diameter));
		MOCK_NON_CONST_METHOD(SetScrewVisiblity, 1, void(bool isVisible));
		MOCK_NON_CONST_METHOD(SetPlanCentricViewAngle, 1, void(double angle));
		MOCK_NON_CONST_METHOD(DeletePlan, 0, void());
	};

}