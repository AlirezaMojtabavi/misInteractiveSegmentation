#include "stdafx.h"
#include "..\Header\CTSkinFilledColorMap.h"
#include <boost/range/iterator_range.hpp>


CTSkinFilledColorMap::CTSkinFilledColorMap(double minThreshold, double maxThreshold)
	: m_MinThreshold(minThreshold), m_MaxThreshold(maxThreshold)
{


}

misColorListTypedef CTSkinFilledColorMap::GetColorMap(bool useDefaultColor, const misColorStruct& objectColor) const
{
	misColorListTypedef colorList;
	misColorStruct        rawColor;
	if (!useDefaultColor)
	{
		rawColor = objectColor;
	}
	else
	{
		rawColor.red = 250;
		rawColor.green = 220;
		rawColor.blue = 160;
	}
	rawColor.alpha = 0.0;
	colorList[m_MinThreshold - 1] = rawColor;
	rawColor.alpha = 0.1;
	colorList[m_MinThreshold] = rawColor;
	rawColor.ChangeColor(10, 10, 10);
	rawColor.alpha = 1.0;
	double val = m_MinThreshold + 200;
	if (val > m_MaxThreshold)
	{
		val = (m_MinThreshold + m_MaxThreshold) / 2;
	}
	colorList[val] = rawColor;
		rawColor.ChangeColor(10, 10, 10);
	rawColor.alpha = 1.0;
	if (m_MaxThreshold - m_MinThreshold > 3000)
	{
		rawColor.red = 240;
		rawColor.green = 240;
		rawColor.blue = 240;
		colorList[2900] = rawColor;
		rawColor.ChangeColor(255, 255, 255);
		colorList[3500] = rawColor;
	}
	else
		{
			colorList[m_MaxThreshold] = rawColor;
		}

		rawColor.alpha = 0.0;
		colorList[m_MaxThreshold + 1] = rawColor;
		return colorList;
}

void CTSkinFilledColorMap::SetViewingThreshold(bool useDefaultThreshold, double minThreshold)
{
	m_MinThreshold = minThreshold;
	if (useDefaultThreshold)
	{
		m_MinThreshold = -500.0;
		const auto range = 3500.0;
		m_MaxThreshold = m_MinThreshold + range;
	}
	else
	{
		if (minThreshold > -75)
			m_MinThreshold = -75;
		const auto range = 3500.0;
		m_MaxThreshold = m_MinThreshold + range;
	}
}

void CTSkinFilledColorMap::SetMinThreshold(double value)
{
	m_MinThreshold = value;
}

void CTSkinFilledColorMap::SetMaxThreshold(double value)
{
	m_MaxThreshold = value;
}

 