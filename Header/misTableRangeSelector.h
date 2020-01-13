#pragma once
#include "misStrctDicomHeaderInfo.h"
// fitting a range for generating texture - if you want to active texture erasing(texture erasing use double as real 
// image range  )you must set this range 2 * image range
class misTableRangeSelector
{
public:
	misTableRangeSelector(misImageingProperties imageProp, double minScalaRange, double maxScalarRange );
	std::vector<double> GetRange() const;
private:
	misImageingProperties m_ImageProp;
	double m_MinScalarRange;
	double m_MaxScalarRange;
	std::vector<double> m_TableRange;
};

