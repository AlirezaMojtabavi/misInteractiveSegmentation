#pragma once
#include "ITracker.h"
#include "IBiopsyToolTransformCalculatorTracker.h"
#include "IBiopsyToolDetector.h"

class misTrackerFactory
{
public:

	static std::shared_ptr<ITracker> CreateTracker(TrackerType trackerType);
	static std::shared_ptr<ITracker> CreateBiopsyTracker(
		std::shared_ptr<parcast::IBiopsyToolTransformCalculatorTracker> toolTransformCalculator,
		std::shared_ptr<parcast::IBiopsyToolDetector> biopsyToolDetector);
};

