#pragma once
#include "VisualizationGeneralTypes.h"
#include "IScrewCompound.h"

class misScrewWidgetData;

class IInitializeScrewWidget
{
public:
	virtual ~IInitializeScrewWidget() = default;
	virtual std::shared_ptr<IScrewCompound> Initialize(const misScrewWidgetData& initVals, IMAGEORIENTATION orientation)
	= 0;
};
