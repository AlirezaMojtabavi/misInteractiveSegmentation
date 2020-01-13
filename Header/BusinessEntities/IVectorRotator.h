#pragma once
#include "BusinessEntities\Vector.h"

namespace parcast
{

	class IVectorRotator
	{
	public:
		using VectorType = parcast::Vector<double, 3>;

		virtual ~IVectorRotator() = default;

		virtual VectorType Rotate(const VectorType& vector, const VectorType& axis, double angle) = 0;
	};

}
