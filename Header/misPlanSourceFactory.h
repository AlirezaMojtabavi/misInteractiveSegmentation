#pragma once
#include "IPlanSourceFactory.h"
#include "misApplication.h"

class misPlanSourceFactory: public IPlanSourceFactory
{
public:
	std::shared_ptr<IImplantSource> CreatePlanSource(
		std::shared_ptr<ICornerProperties> cornerProperties ,IMAGEORIENTATION orientaion, misApplicationType, bool displayCross) override;
};
