#pragma once
#include "misSimplePointType.h"
#include "misROI.h"

class misSeedBoundingCalculator
{
public:
	misSeedBoundingCalculator(misSimplePointListType tFGSeedList);
	misROI GetSeedBounding(int* dimenstion, double* spacing);	
private:

	double clip(double nnumber, double lower, double upper);

	misSimplePointListType m_FGSeedList;
	misSimplePointListType m_BGSeedList;


};

