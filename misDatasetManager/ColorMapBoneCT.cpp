#include "stdafx.h"
#include "ColorMapBoneCT.h"
#include <boost/range/iterator_range.hpp>


ColorMapBoneCT::ColorMapBoneCT(double minThreshold, double maxThreshold)
	: m_MaxThreshold(maxThreshold),
	  m_MinThreshold(minThreshold)
{
}

void ColorMapBoneCT::SetViewingThreshold( bool usedDefaultThreshold, double minThreshold)
{
	const auto  range = 2400;
	if (usedDefaultThreshold)
	{
		m_MinThreshold = 250;
		m_MaxThreshold = m_MinThreshold + range;
	}
	 
	else
	{
 		m_MaxThreshold = m_MinThreshold + range;

	}
 
}

void ColorMapBoneCT::SetMinThreshold(double value)
{
	m_MinThreshold = value;
}

void ColorMapBoneCT::SetMaxThreshold(double value)
{
	m_MaxThreshold = value;
}


misColorListTypedef ColorMapBoneCT::GetColorMap(bool useDefaultThreshold, const misColorStruct& objectColor) const
{
	misColorListTypedef   colorList;
	if (useDefaultThreshold)
	{
		misColorStruct redColor;
		redColor.red = 229;
		redColor.green = 40;
		redColor.blue = 20;
		redColor.alpha = 0.0;
		colorList[m_MinThreshold - 1] = redColor;
		redColor.alpha = 0.2;
		colorList[m_MinThreshold] = redColor;
		misColorStruct sunflowerColor;
		sunflowerColor.red = 229;
		sunflowerColor.green = 203;
		sunflowerColor.blue = 138;
		sunflowerColor.alpha = 1.0;
		colorList[m_MinThreshold + 100] = sunflowerColor;
		colorList[m_MinThreshold + 269] = sunflowerColor;
		sunflowerColor.ChangeColor( 25, 20, 5);
		sunflowerColor.alpha = 1.0;
		colorList[m_MaxThreshold] = sunflowerColor;
		sunflowerColor.alpha = 0;
		colorList[m_MaxThreshold + 1] = sunflowerColor;
	}
	else
	{
		misColorStruct redColor(255,0,0,1.0);
		misColorStruct whiteColor(249,255,255,0.36);
		auto color = objectColor;
		redColor.alpha = 0.0;
		colorList[m_MinThreshold - 1] = redColor;
		redColor.alpha = 0.0;
		colorList[m_MinThreshold+150] = redColor;
		redColor.alpha = 1.0;
		colorList[m_MinThreshold + 265] = whiteColor;
		color.alpha = 1.0;
		colorList[m_MinThreshold + 968] = color;
		color.alpha = 0;
		colorList[m_MaxThreshold + 1] = color;
	}
	return colorList;
}

   