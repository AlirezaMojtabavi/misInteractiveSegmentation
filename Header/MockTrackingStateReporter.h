#pragma once

#include <boost/test/auto_unit_test.hpp>
#include <turtle/mock.hpp>

#include "ITrackingStateReporter.h"

MOCK_BASE_CLASS(MockTrackingStateReporter, ITrackingStateReporter)
{
	MOCK_NON_CONST_METHOD(GenerateReport, 1, misTrackingStateReport ());
};