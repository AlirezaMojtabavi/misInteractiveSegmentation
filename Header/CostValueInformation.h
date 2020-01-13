#ifndef _CostValueInformation_h
#define _CostValueInformation_h

struct CostValueInformation
{
	unsigned int IterationsNumber;
	int LevelIndex;
	double CostValue;

	CostValueInformation()
	{
		IterationsNumber = 0;
		LevelIndex = -1;
		CostValue = 0.0;
	}
};

#endif