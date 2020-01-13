#pragma once

#include "IPackage.h"

namespace parcast
{

	MOCK_BASE_CLASS(MockPackage, IPackage)
	{
		MOCK_NON_CONST_METHOD(DeletePackage, 0, void());
	};

}