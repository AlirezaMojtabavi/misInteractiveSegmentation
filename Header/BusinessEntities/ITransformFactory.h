#pragma once

#include "ITransform.h"

namespace parcast
{

	class ITransformFactory
	{
	public:
        virtual std::shared_ptr<ITransform> Create(const double matrixElements[16]) const = 0;
        virtual std::unique_ptr<ITransform> CreateUptr(const double matrixElements[16]) const = 0;

		virtual ~ITransformFactory() = default;
	};

}
