#pragma  once

#include "misROI.h"

class misImageIOProperties
{
public:
	int    NumberOfComponent;
	int    extent[6];
	double spacing[3];
	int    scalerType;
	int    fileDimensionality;
	int	   FOVExtent[6];

	misImageIOProperties();;
	misROI GetRoi() const;
	void SetRoi(const misROI& val);
	void Reset(void);;

private:
	misROI      m_Roi;
};
