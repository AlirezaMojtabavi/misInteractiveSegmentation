#pragma once
class IAddFixedLandmarks
{
public:
	virtual ~IAddFixedLandmarks() = default;

	virtual void AddLandmarks(misLandmarkListTypdef landmarks) = 0;
};
