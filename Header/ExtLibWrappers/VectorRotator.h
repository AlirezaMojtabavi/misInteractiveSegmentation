#pragma once
#include "IVectorRotator.h"

namespace  parcast
{

	class VectorRotator : public IVectorRotator
	{
	public:
		VectorType Rotate(const VectorType& vector, const VectorType& axis, double angle/*In Degrees*/) override;
	};

}
