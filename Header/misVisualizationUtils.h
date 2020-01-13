#pragma once

#include "VisualizationGeneralTypes.h"

class   misVisualizationUtils
{
public:
	misVisualizationUtils(void);
	static bool CheckInFrustum(double* bounds, double*              planes);
	~misVisualizationUtils(void);
	
};
