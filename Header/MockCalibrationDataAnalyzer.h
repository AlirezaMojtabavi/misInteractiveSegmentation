#pragma once

#include <boost/test/auto_unit_test.hpp>
#include <turtle/mock.hpp>

#include "ICalibrationDataAnalyzer.h"

MOCK_BASE_CLASS(MockCalibrationDataAnalyzer, ICalibrationDataAnalyzer)
{
	MOCK_NON_CONST_METHOD(Push, 1, void (std::shared_ptr<const ITransform> element));
	MOCK_CONST_METHOD(GetDataBuffer, 0, const misCalibrationDataBuffer&());
	MOCK_NON_CONST_METHOD(Clear, 0, void ());
	MOCK_NON_CONST_METHOD(SetDataBufferLength, 1, void (int));
	MOCK_CONST_METHOD(GetDataBufferLength, 0, int ());
	MOCK_CONST_METHOD(IsDataUsable, 0, bool ());
	MOCK_CONST_METHOD(GetCurrentProgress, 0, double ());
};