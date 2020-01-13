#pragma once

#include "IVectorRotator.h"

namespace parcast
{

	MOCK_BASE_CLASS(MockVectorRotator, IVectorRotator)
	{
		MOCK_NON_CONST_METHOD(Rotate, 3, VectorType(const VectorType& vector, const VectorType& axis, double angle));
	};

}