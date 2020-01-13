#include "stdafx.h"
#include "..\Header\CTSinusViewingColorMap.h"





misColorListTypedef CTSinusViewingColorMap::GetColorMap(bool useDefaultColor, const misColorStruct& objectColor) const
{

	misColorStruct  rawColor;
	rawColor.red = 250;
	rawColor.green = 220;
	rawColor.blue = 160;
	const double minThresholdSkin = -700;
	rawColor.alpha = 0.0;
	misColorListTypedef colorList;
	colorList[minThresholdSkin - 1] = rawColor;
	rawColor.alpha = 0.05;
	colorList[minThresholdSkin] = rawColor;
	rawColor.ChangeColor(10, 10, 10);
	rawColor.alpha = 0.05;
	colorList[minThresholdSkin + 150] = rawColor;
	rawColor.ChangeColor(10, 10, 10);
	rawColor.alpha = 0.05;
	colorList[-200] = rawColor;
	rawColor.ChangeColor(10, 10, 10);
	rawColor.alpha = 0.05;
	colorList[-150] = rawColor;
	rawColor.alpha = 0.0;
	colorList[-130] = rawColor;
	const double minThresholdBone = 150;
	rawColor.red = 229;
	rawColor.green = 40;
	rawColor.blue = 20;
	rawColor.alpha = 0.0;
	colorList[minThresholdBone - 1] = rawColor;
	rawColor.red = 229;
	rawColor.green = 80;
	rawColor.blue = 60;
	rawColor.alpha = 0.2;
	colorList[minThresholdBone] = rawColor;
	rawColor.red = 229;
	rawColor.green = 203;
	rawColor.blue = 138;
	rawColor.alpha = 1.0;
	colorList[minThresholdBone + 100] = rawColor;
	rawColor.alpha = 1.0;
	colorList[minThresholdBone + 269] = rawColor;
	rawColor.ChangeColor(25, 20, 5);
	rawColor.alpha = 1.0;
	colorList[minThresholdBone + 2800] = rawColor;
	rawColor.red = 0;
	rawColor.green = 155;
	rawColor.blue = 255;
	rawColor.alpha = 1.0;
	colorList[minThresholdBone + 2800 + 1] = rawColor;
	rawColor.red = 0;
	rawColor.green = 75;
	rawColor.blue = 255;
	rawColor.alpha = 1.0;
	colorList[3000] = rawColor;
	rawColor.red = 0;
	rawColor.green = 0;
	rawColor.blue = 255;
	rawColor.alpha = 1.0;
	colorList[3500] = rawColor;
	rawColor.alpha = 0.0;
	colorList[3501] = rawColor;
	return colorList;
}


void CTSinusViewingColorMap::SetViewingThreshold(bool useDefaultThreshold, double minThreshold)
{
	const auto range = 2500;
	m_MinThreshold = minThreshold;
	if (useDefaultThreshold)
	{
		m_MinThreshold = -300;

	}
	m_MaxThreshold = m_MinThreshold + range;

}

void CTSinusViewingColorMap::SetMinThreshold(double value)
{
	m_MinThreshold = value;
}

void CTSinusViewingColorMap::SetMaxThreshold(double value)
{
	m_MaxThreshold = value;
}
