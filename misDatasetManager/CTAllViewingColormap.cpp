#include "stdafx.h"
#include "CTAllViewingColormap.h"


ctAllViewingColormap::ctAllViewingColormap(double minThreshold, double maxThreshold)
	:m_MinThreshold(minThreshold),
	m_MaxThreshold(maxThreshold)
{
}


 

misColorListTypedef ctAllViewingColormap::GetColorMap(bool useDefaultColor, const misColorStruct& objectColor) const
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
		//***************------------------------------
		rawColor.alpha = 0.1;
		colorList[m_MinThreshold] = rawColor;
		rawColor.ChangeColor(10, 10, 10);
		rawColor.alpha = 1.0;
		colorList[m_MinThreshold + 200] = rawColor;
		//***************------------------------------

		rawColor.ChangeColor(10, 10, 10);
		rawColor.alpha = 1.0;
		colorList[150] = rawColor;
		///////////////   bony parts
		rawColor.red = 229;
		rawColor.green = 40;
		rawColor.blue = 20;
		colorList[225] = rawColor;

		rawColor.red = 240;
		rawColor.green = 240;
		rawColor.blue = 240;
		colorList[400] = rawColor;

		rawColor.red = 255;
		rawColor.green = 255;
		rawColor.blue = 255;
		colorList[3500] = rawColor;

		rawColor.alpha = 0.0;
		colorList[3500 + 1] = rawColor;


	return colorList;
 
}

void ctAllViewingColormap::SetViewingThreshold(bool useDefaultThreshold, double minThreshold)
{
	const auto range = 4000;
	m_MinThreshold = minThreshold;
	if (useDefaultThreshold)
	{
		m_MinThreshold = -300.0;
	}
	m_MaxThreshold = m_MinThreshold + range;

}

void ctAllViewingColormap::SetMinThreshold(double value)
{
	m_MinThreshold = value;
}

void ctAllViewingColormap::SetMaxThreshold(double value)
{
	m_MaxThreshold = value;
}
