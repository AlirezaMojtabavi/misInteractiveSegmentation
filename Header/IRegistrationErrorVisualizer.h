#pragma once
#include "BusinessEntities\Point.h"
class IRegistrationErrorVisualizer
{
public:
	virtual void HideRegistrationErrorLandmark(void) = 0;
	virtual void ShowRegistrationErrorLandmark() = 0;
	virtual void SetFinalRegisteredPosition(parcast::Point<double, 3> val) = 0;
};
