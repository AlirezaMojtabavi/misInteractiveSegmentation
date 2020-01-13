#include "stdafx.h"
#include "MRSkinFilledColorMap.h"
#include "IMRIColoredColorMap.h"
#include "misMRICOloredColorMap.h"


MRSkinFilledColorMap::MRSkinFilledColorMap(std::shared_ptr<ITFIAddressMapper> tfiMap, std::shared_ptr<ITFILoader> TFILoader)
	: m_TFILoader(TFILoader),
	m_TFIAddMap(tfiMap)
{
}

misColorListTypedef MRSkinFilledColorMap::GetColorMap(bool useDefaultColor, const misColorStruct& objectColor) const
{

	const std::unique_ptr<IMRIColoredColorMap> colormap =
		std::make_unique<misMRIColoredColorMap>(m_TFIAddMap, m_TFILoader, misVolumeViewingTypes::misSkinFilledViewing);

	misColorListTypedef	colorList = colormap->GetColorList();
	auto minIntensityDiff = std::abs(colorList.begin()->first - m_MinThreshold);
	colorList[m_MinThreshold] = colorList.begin()->second;
	colorList[m_MinThreshold].alpha = 0;

	for (auto itter = colorList.begin(); itter != colorList.end(); ++itter)
	{
		if (itter->first < m_MinThreshold)
			itter->second.alpha = 0;

		else if (std::abs(itter->first - m_MinThreshold) < minIntensityDiff)
		{
			colorList[m_MinThreshold] = itter->second;
			colorList[m_MinThreshold].alpha = 0.5;
			minIntensityDiff = std::abs(itter->first - m_MinThreshold);
		}
		else if (itter->first >= m_MinThreshold && useDefaultColor)
		{
			itter->second.alpha = 1;
		}
		else if (itter->first >= m_MinThreshold && !useDefaultColor)
		{
			itter->second = objectColor;
		}
	}
	return colorList;
}

void MRSkinFilledColorMap::SetViewingThreshold(bool useDefaultThreshold, double minThreshold)
{
	const auto range = 2000;
	m_MinThreshold = minThreshold;
	if (useDefaultThreshold)
	{
		m_MinThreshold = 900;
	}
	m_MaxThreshold = m_MinThreshold + range;
}

void MRSkinFilledColorMap::SetMinThreshold(double value)
{
	m_MinThreshold = value;
}

void MRSkinFilledColorMap::SetMaxThreshold(double value)
{
	m_MaxThreshold = value;
}
