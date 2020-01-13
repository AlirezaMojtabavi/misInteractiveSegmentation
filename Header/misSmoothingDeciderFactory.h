#pragma once
#include "IAppySmoothingDecider.h"
class misSmoothingDeciderAbstarctFactory
{
public:
	 virtual std::shared_ptr<IApplySmoothingDecider> CreateSmothing() = 0;
};

