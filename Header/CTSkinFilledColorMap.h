#pragma once
#include "misColorStruct.h"
 #include "IColorMapGenerator.h"

class CTSkinFilledColorMap : public IColorMapGenerator
{
public:
	CTSkinFilledColorMap(double minThreshold, double maxThreshold);

	misColorListTypedef GetColorMap(bool useDefaultColor, const misColorStruct& objectColor) const override;
	void SetViewingThreshold(bool useDefaultThreshold, double minThreshold)
	override;
	void SetMinThreshold(double) override;
	void SetMaxThreshold(double) override;
  private:
	double m_MinThreshold = 0;
	double m_MaxThreshold = 0;

};

