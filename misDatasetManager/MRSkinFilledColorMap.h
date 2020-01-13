#pragma once
#include "IColorMapGenerator.h"
#include <ITFIAddressMapper.h>
#include "ITFILoader.h"

class MRSkinFilledColorMap :
	public IColorMapGenerator
{
public:
	MRSkinFilledColorMap(std::shared_ptr<ITFIAddressMapper> tfiMap, std::shared_ptr<ITFILoader> TFILoader);

	misColorListTypedef GetColorMap(bool useDefaultColor, const misColorStruct& objectColor) const override;
	void SetViewingThreshold(bool useDefaultThreshold, double minThreshold)
		override;
	void SetMinThreshold(double) override;
	void SetMaxThreshold(double) override;
private:
	double m_MinThreshold = 0;
	double m_MaxThreshold = 0;
	std::shared_ptr<ITFILoader> m_TFILoader;
	std::shared_ptr<ITFIAddressMapper> m_TFIAddMap;
};

