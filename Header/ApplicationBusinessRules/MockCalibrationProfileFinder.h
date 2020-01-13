#pragma once

#include "ICalibrationProfileFinder.h"

namespace parcast
{

	MOCK_BASE_CLASS(MockCalibrationProfileFinder, ICalibrationProfileFinder)
	{
		MOCK_CONST_METHOD(Get, 0, CalibrationProfile());
		MOCK_NON_CONST_METHOD(SetUserType, 1, void(const std::string& userType));
		MOCK_NON_CONST_METHOD(SetSubjectTrackingTool, 1, void(std::shared_ptr<ITrackingTool> trackingTool));
	};

}