#pragma once
struct misSliderStrc;

class 	IVolumeThresholdUiUpdater
{
public:
	virtual ~IVolumeThresholdUiUpdater() = default;

	virtual void UpdateThreshold(const misSliderStrc& sliderRange) const = 0;

};
