#pragma once
#include "misPolarisTrackerWrapper.h"
#include "IBiopsyToolTransformCalculatorTracker.h"

class misBiopsyPolarisTrackerWrapper : public misPolarisTrackerWrapper
{

public:
	misBiopsyPolarisTrackerWrapper(igstk::PolarisTracker* tracker, std::shared_ptr<parcast::IBiopsyToolTransformCalculatorTracker> toolTransformCalculator);
};
