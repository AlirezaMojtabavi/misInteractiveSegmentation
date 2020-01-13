#pragma once

#include <turtle/mock.hpp>

#include "ICoordinateSystem.h"

MOCK_BASE_CLASS(MockCoordinateSystem, ICoordinateSystem)
{
	MOCK_NON_CONST_METHOD(SetUID, 1, void (const std::string& id));
	MOCK_CONST_METHOD(GetUID, 0, std::string ());
};