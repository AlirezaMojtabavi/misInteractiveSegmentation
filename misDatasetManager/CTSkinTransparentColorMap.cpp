#include "stdafx.h"
#include "CTSkinTransparentColorMap.h"

 

CTSkinTransparentColorMap::CTSkinTransparentColorMap(double minThreshold, double maxThreshold)
	: m_MinThreshold(minThreshold), m_MaxThreshold(maxThreshold)
{

}

misColorListTypedef CTSkinTransparentColorMap::GetColorMap(bool useDefaultColor, const misColorStruct& objectColor) const
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
	rawColor.alpha = 0.067;
	colorList[m_MinThreshold] = rawColor;
	rawColor.ChangeColor(10, 10, 10);
	rawColor.alpha = 0.67;
	double val = m_MinThreshold + 200;
	if (val > m_MaxThreshold)
	{
		val = (m_MinThreshold + m_MaxThreshold) / 2;
	}
	colorList[val] = rawColor;
	rawColor.ChangeColor(10, 10, 10);
	rawColor.alpha = 0.67;
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

void CTSkinTransparentColorMap::SetViewingThreshold( bool useDefaultThreshold, double minThreshold)
{
	m_MinThreshold = minThreshold;
	if (useDefaultThreshold)
	{
		m_MinThreshold = -600;
		const auto range = 450.0;
		m_MaxThreshold = m_MinThreshold + range;
	}
	else
	{
		minThreshold = m_MinThreshold;
		// the min threshold for skin must be minus surely
		if (m_MinThreshold > -150)
			m_MinThreshold = -150;
		auto range = -150.0 - minThreshold;
		if (range > 400)
		{
			range = 400;
		}
		if (range < 100)
			range = 100;
		m_MaxThreshold = m_MinThreshold + range;

	}
}

void CTSkinTransparentColorMap::SetMinThreshold(double value )
{
	m_MinThreshold = value;
}

void CTSkinTransparentColorMap::SetMaxThreshold(double value)
{
	m_MaxThreshold = value;
}

 