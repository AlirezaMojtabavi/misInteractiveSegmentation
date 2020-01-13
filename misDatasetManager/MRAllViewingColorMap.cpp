#include "stdafx.h"
#include "MRAllViewingColorMap.h"
#include "IMRIColoredColorMap.h"
#include "misMRICOloredColorMap.h"
#include "misTFILoader.h"


mrAllViewingColorMap::mrAllViewingColorMap(std::shared_ptr<ITFIAddressMapper> tfiMap, std::shared_ptr<ITFILoader> TFILoader)
	: m_TFILoader(TFILoader),
	m_TFIAddMap(tfiMap)

{
}


misColorListTypedef mrAllViewingColorMap::GetColorMap(bool useDefaultColor, const misColorStruct& objectColor) const
{
	const std::unique_ptr<IMRIColoredColorMap> colormap =
		std::make_unique<misMRIColoredColorMap>(m_TFIAddMap, m_TFILoader, misVolumeViewingTypes::misAllViewing);

	misColorListTypedef	colorList = colormap->GetColorList();
	auto minIntensityDiff = std::abs(colorList.begin()->first - m_MinThreshold);
	colorList[m_MinThreshold] = colorList.begin()->second;
	colorList[m_MinThreshold].alpha = 0;
	for (auto itter = colorList.begin(); itter != colorList.end(); ++itter)
	{
		if (itter->first < m_MinThreshold)
			itter->second.alpha = 0;

		if (itter->first == m_MinThreshold)
			continue;

		if (std::abs(itter->first - m_MinThreshold) < minIntensityDiff)
		{
			colorList[m_MinThreshold] = itter->second;
			colorList[m_MinThreshold].alpha = 0;
			minIntensityDiff = std::abs(itter->first - m_MinThreshold);
		}
	}
	return colorList;

}

void mrAllViewingColorMap::SetViewingThreshold(bool useDefaultThreshold, double minThreshold)
{
	const auto range = 2000.0;
	m_MinThreshold = minThreshold;
	if (useDefaultThreshold)
	{
		m_MinThreshold = 158;
	}
	m_MaxThreshold = m_MinThreshold + range;

 }

void mrAllViewingColorMap::SetMinThreshold(double value )
{
	m_MinThreshold = value;
}

void mrAllViewingColorMap::SetMaxThreshold(double value)
{
	m_MaxThreshold = value;
}
