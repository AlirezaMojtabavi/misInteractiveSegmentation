#pragma once
#include "IColorMapGenerator.h"

class ColorMapBoneCT :
	public IColorMapGenerator
{
public:
	ColorMapBoneCT(double minThreshold, double maxThreshold);
 
 	void SetViewingThreshold(bool useDefaultColor, double minThreshold) override;
 	void SetMinThreshold(double) override;
	void SetMaxThreshold(double) override;
 	misColorListTypedef GetColorMap(bool useDefaultThreshold, const misColorStruct& objectColor) const override;


private:
	double m_MinThreshold = 0;
	double m_MaxThreshold = 0;
};

