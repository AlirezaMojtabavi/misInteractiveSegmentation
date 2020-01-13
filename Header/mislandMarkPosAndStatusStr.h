#pragma once

#include "misLandmarkenums.h"
#include "misSimplePointType.h"

struct mislandMarkPosAndStatusStr
{
	misSimplePointType position;
	LandmarkStatus     status;
	double             error;
	
	// Flag that is set if last point must be selected.
	bool m_LastView;

	void Reset(void)
	{
		position.SetPoint(-1, -1, -1);

		status = InvalidPoint;
		error = -1;
	};
	mislandMarkPosAndStatusStr()
	{
		this->Reset();
	};
	
};
