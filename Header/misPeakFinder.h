#pragma once

#include "misLibraryMacroes.h"
#include "misMacros.h"
#include "misSeconderyNeededHeader.h"

class MISLIBRARYEXPORT  misPeakFinder
{
private:
	struct paekDataStr
	{
		int    index;
		double value;
	};

	std::vector<paekDataStr>   m_PeakDatas;
	std::vector<double>        m_GradientInputArray;
	std::vector<double>        m_MainInputArray;

	int                  m_PeakIndex;

	double               m_MinPeakAbs;
	int                  m_MinummimdDistanceBetweenPeaks;
	double               m_GradientThreshold;

public:
	//void SetPeakFinderMethodToThreshold(void)  {this->m_method = false;};
	//void SetPeakFiderMethodToRatioToPeak(void) {this->m_method = true; };
	misPrivateBooleanVariableWithPublicAccessorsMacro(m_FindIndexBasedOnThreshold, FindIndexBasedOnThreshold);
	misCreateVariableWithSetGetMacro(Threshold,double);
	misCreateVariableWithSetGetMacro(RatioToPeak,double);

	void SetGradientValueList(std::vector<double> inputArray);
	void SetMainValueList(std::vector<double> inputArray);
    int  GetPeakIndex(void);

public:
	misPeakFinder(void);
	~misPeakFinder(void);

private:
	void UpdateGradientThreshold(void);
	void Compute(void);
	void ExtractPeaks(void);
	void ExtractIndex(void);
	void EliminateNearPoints(void);
	void ExtractPeaksBasedOnThreshold( void );
};
