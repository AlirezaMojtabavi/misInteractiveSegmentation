#pragma once

#include "ICoordinateSystemDataAccess.h"

namespace parcast
{

	MOCK_BASE_CLASS(MockCoordinateSystemDataAccess, ICoordinateSystemDataAccess)
	{
		MOCK_NON_CONST_METHOD(InsertIfNotExists, 1, void(const std::string& coordinateSystemUid));
		MOCK_NON_CONST_METHOD(Delete, 1, void(const std::string& coordinateSystemUid));
	};

}