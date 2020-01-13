#pragma once

#include "ITransformFactory.h"

namespace parcast
{

	class TransformFactory : public ITransformFactory
	{
	public:
		std::shared_ptr<ITransform> Create(const double matrixElements[16]) const;
        std::unique_ptr<ITransform> CreateUptr(const double matrixElements[16]) const;
    };

}
