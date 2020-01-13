#pragma once

#include "misCalculateDistance.h"

 

class mis3DMeasurmentControl :public misCalculateDistance
{

public:
   
	mis3DMeasurmentControl(void);
	~mis3DMeasurmentControl(void);

	void Reset(void);
	bool SetPointerPosition(const double pos[3]);


private:
	void ComputeStaticDistanse();
	void ComputeDynamicDistance(const double pos[3]);
};

