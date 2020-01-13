#pragma once

#include <boost/test/auto_unit_test.hpp>
#include <turtle/mock.hpp>

#include "ICalibrationStrategy.h"

MOCK_BASE_CLASS(MockCalibrationStrategy, ICalibrationStrategy)
{
	MOCK_NON_CONST_METHOD(SetDataBuffer, 1, void (const misCalibrationDataBuffer& buffer));
	MOCK_CONST_METHOD(GetDataBuffer, 0, const misCalibrationDataBuffer& ());
	MOCK_CONST_METHOD(GetCalibrationTransform, 0, std::shared_ptr<ITransform> ());
};