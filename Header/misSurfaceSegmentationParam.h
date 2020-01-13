#pragma once

#include "misSimplePointType.h"
#include "serializable.h"
 
class misSurfaceSegmentationParam:public  Serializable
{
public:
	misSimplePointListType m_FGSeedList;
	misSimplePointListType m_BGSeedList;

	bool         m_SetROI;
	bool		 PreMaxThreshold;
	bool		 PreMinThreshold;
	bool		 m_UseThreadForSegmentation;
	bool		 m_NewSegmentationHasBeenDone;

	float		 MaxFG;
	float		 MinFG;
	float		 FGMean;
	float		 BGLightMean;
	float		 BGDarkMean;
	float		 FGVariance;
	float		 BGLightVariance;
	float		 BGDarkVariance;
	float		 m_UpperThreshold;
	float		 m_LowerThreshold;

	float m_LeftIncreasingRate; 
	float m_LeftDecreasingRate; 
	float m_RightIncreasingRate;
	float m_RightDecreasingRate;
	misSurfaceSegmentationParam(void);
	~misSurfaceSegmentationParam(void);
};

