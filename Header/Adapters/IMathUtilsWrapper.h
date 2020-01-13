#pragma once

#include "BusinessEntities\Vector.h"

namespace parcast
{
	typedef Vector<double, 3> VectorType;
	class IMathUtilsWrapper
	{
	public:
		virtual VectorType&& CrossProduct(const VectorType& vect1,const VectorType& vect2) const = 0;
	};
}