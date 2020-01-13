#pragma once

#include "IMathUtilsWrapper.h"

namespace parcast
{
	
	MOCK_BASE_CLASS(MockMathUtilsWrapper, IMathUtilsWrapper)
	{
		MOCK_CONST_METHOD(CrossProduct, 2, VectorType&&(const VectorType& vect1, const VectorType& vect2));
	};
}
