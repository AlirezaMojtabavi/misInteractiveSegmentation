#include "stdafx.h"
#include "MRSkinTransparentColorMap.h"
#include "IMRIColoredColorMap.h"
#include "misMRICOloredColorMap.h"


MRSkinTransparentColorMap::MRSkinTransparentColorMap(std::shared_ptr<ITFIAddressMapper> tfiMap, std::shared_ptr<ITFILoader> TFILoader)
	: m_TFILoader(TFILoader),
	m_TFIAddMap(tfiMap)
{
}

misColorListTypedef MRSkinTransparentColorMap::GetColorMap(bool useDefaultColor, const misColorStruct& objectColor) const
{
	const std::unique_ptr<IMRIColoredColorMap> colormap =
		std::make_unique<misMRIColoredColorMap>(m_TFIAddMap, m_TFILoader, misVolumeViewingTypes::misSkinviewing);

	misColorListTypedef	colorList = colormap->GetColorList();
	auto minIntensityDiff = std::abs(colorList.begin()->first - m_MinThreshold);
	colorList[m_MinThreshold] = colorList.begin()->second;
	colorList[m_MinThreshold].alpha = 0;

	for (auto itter = colorList.begin(); itter != colorList.end(); ++itter)
	{
		if (itter->first < m_MinThreshold)
			itter->second.alpha = 0;

		if (std::abs(itter->first - m_MinThreshold) < minIntensityDiff && useDefaultColor)
		{
			colorList[m_MinThreshold] = itter->second;
			colorList[m_MinThreshold].alpha = 0;
			minIntensityDiff = std::abs(itter->first - m_MinThreshold);
		}
		if (itter->first >= m_MinThreshold && !useDefaultColor)
		{
			itter->second = objectColor;
		}
	}
	return colorList;
}

void MRSkinTransparentColorMap::SetViewingThreshold(bool useDefaultThreshold, double minThreshold)
{
	const auto range = 500;
	m_MinThreshold = minThreshold;
	if (useDefaultThreshold)
	{
		m_MinThreshold = 900;
	}
	m_MaxThreshold = m_MinThreshold + range;
}

void MRSkinTransparentColorMap::SetMinThreshold(double value)
{
	m_MinThreshold = value;
}

void MRSkinTransparentColorMap::SetMaxThreshold(double value)
{
	m_MaxThreshold = value;
}
