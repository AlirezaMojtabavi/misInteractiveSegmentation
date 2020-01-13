#pragma once
#include "IPlanSourceFactory.h"
MOCK_BASE_CLASS(MockPlanSourceFactory, IPlanSourceFactory)
{
	MOCK_NON_CONST_METHOD(CreatePlanSource, 3, std::shared_ptr<IImplantSource> (std::shared_ptr<ICornerProperties> ,IMAGEORIENTATION orientaion, misApplicationType) );
};