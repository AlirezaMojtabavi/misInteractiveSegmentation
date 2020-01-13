#pragma once
#include "IImplantSource.h"
#include "VisualizationGeneralTypes.h"
#include "ICornerProperties.h"
#include "misApplication.h"

class IPlanSourceFactory
{
public:
	virtual ~IPlanSourceFactory() = default;
	virtual std::shared_ptr<IImplantSource> CreatePlanSource(std::shared_ptr<ICornerProperties> cornerProperties,
	                                                         IMAGEORIENTATION orientaion, misApplicationType, bool displayCross) = 0;
};
