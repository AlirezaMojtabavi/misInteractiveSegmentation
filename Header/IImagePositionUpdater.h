#pragma once
#include "BusinessEntities\Point.h"
class IImagePositionUpdater
{
public:
	virtual void UpdatePosition(parcast::Point<double, 3> position) = 0;
	virtual void SetVirtualTipExtend(double lenght) = 0;

};

 