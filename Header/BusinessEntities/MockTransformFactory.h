#pragma once

#include "ITransformFactory.h"

namespace parcast
{

	MOCK_BASE_CLASS(MockTransformFactory, ITransformFactory)
	{
		MOCK_CONST_METHOD(Create, 1, std::shared_ptr<ITransform>(const double matrixElements[16]));
		MOCK_CONST_METHOD(CreateUptr, 1, std::unique_ptr<ITransform>(const double matrixElements[16]));
        
	};

}
