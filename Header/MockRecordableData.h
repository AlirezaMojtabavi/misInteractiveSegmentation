#pragma once

#include <boost/test/auto_unit_test.hpp>
#include <turtle/mock.hpp>

#include "IRecordableData.h"

MOCK_BASE_CLASS(MockRecordableData, IRecordableData)
{
	MOCK_CONST_METHOD(WriteToStream, 1, std::ostream& (std::ostream&))
};