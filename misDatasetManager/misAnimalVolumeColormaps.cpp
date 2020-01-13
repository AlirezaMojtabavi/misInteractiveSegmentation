#include "stdafx.h"
#include "misAnimalVolumeColormaps.h"
#include "misColorStruct.h"
#include "misTFILoader.h"
#include "ITFIAddressMapper.h"
#include "ITFILoader.h"




misAnimalVolumeColormaps::misAnimalVolumeColormaps(std::shared_ptr<ITFIAddressMapper> tfiMap)
	:m_TFILoader(std::make_shared<misTFILoader>()), m_TFIAddMap(tfiMap)
{
	ResetObjectProperties();
}

misAnimalVolumeColormaps::misAnimalVolumeColormaps(std::shared_ptr<ITFIAddressMapper> tfiMap, std::shared_ptr<ITFILoader> TFILoader)
	:
	m_TFIAddMap(tfiMap), m_TFILoader(TFILoader)
{
	ResetObjectProperties();
}

misAnimalVolumeColormaps::~misAnimalVolumeColormaps()
{
}

void misAnimalVolumeColormaps::ResetObjectProperties(void)
{
	m_UseDefaultColor = true;
	m_UsedDefaultThreshold = true;
	m_ImageModality = SPECT;
}

misColorListTypedef misAnimalVolumeColormaps::GetVolumeColorMap()
{
	m_ColorList.clear();
	UpdateThresholds();
	UpdateCTList();
	if (m_VolumeType == misVolumeViewingTypes::misAnimalViewing || m_VolumeType == misVolumeViewingTypes::misSkinFilledViewing || m_VolumeType == misVolumeViewingTypes::misSkinviewing)
		UpdateColorTFIList();
	return m_ColorList;
}

std::unique_ptr<IVolumeRenderingColorMaps> misAnimalVolumeColormaps::clone()
{
	return std::make_unique<misAnimalVolumeColormaps>(*this);
}

void misAnimalVolumeColormaps::SetObjectColor(const misColorStruct& objectColor)
{
	m_ObjectColor = objectColor;
	m_UseDefaultColor = false;
}

void misAnimalVolumeColormaps::SetObjectThreshold(double minThreshold)
{
	m_MinThreshold = minThreshold;
	m_Range = -1;
	m_UsedDefaultThreshold = false;
}

void misAnimalVolumeColormaps::SetObjectThresholdDefault(void)
{
	m_Range = -1;
	m_UsedDefaultThreshold = true;
}

void misAnimalVolumeColormaps::SetObjectThreshold(double minThreshold, double range)
{
	m_MinThreshold = minThreshold;
	if (range < 1)
	{
		range = 1;
	}
	m_Range = range;

	m_UsedDefaultThreshold = false;
}

void misAnimalVolumeColormaps::SetImageModality(misImageDataModality imageModality)
{
	m_UsedDefaultThreshold = true;
	m_ImageModality = imageModality;
}



void misAnimalVolumeColormaps::SetObjectType(misVolumeViewingTypes volumeType)
{
	m_VolumeType = volumeType;
}



void misAnimalVolumeColormaps::UpdateThresholdForAllViewing(double& range)
{
	switch (m_ImageModality)
	{
	case CT:
		if (-1 == m_Range)
			range = 4000;
		else
			range = m_Range;

		if (m_UsedDefaultThreshold)
			SetViewingThreshold(-300, range);
		else
			SetViewingThreshold(m_MinThreshold, range);
		break;

	case MRI:
		if (-1 == m_Range)
			range = 2000;
		else
			range = m_Range;

		if (m_UsedDefaultThreshold)
			SetViewingThreshold(158, range);
		else
			SetViewingThreshold(m_MinThreshold, range);
		break;

	default:
		std::cout << " \n     Unconsidered Image Modality \n";
		if (-1 == m_Range)
			range = 3000;
		else
			range = m_Range;

		if (m_UsedDefaultThreshold)
			SetViewingThreshold(50, range);
		else
			SetViewingThreshold(m_MinThreshold, range);
		break;

	}
}

void misAnimalVolumeColormaps::UpdateThresholds(void)
{
	double range;
	switch (m_VolumeType)
	{
	case misVolumeViewingTypes::misBoneViwing:

		switch (m_ImageModality)
		{
		case CT:
			if (-1 == m_Range)
				range = 2400;
			else
				range = m_Range;

			if (m_UsedDefaultThreshold)
				SetViewingThreshold(250, range);
			else
				SetViewingThreshold(m_MinThreshold, range);
			break;
		default:
			cout << " \n   Unconsidered Image Modality \n ";
			if (-1 == m_Range)
				range = 1000;
			else
				range = m_Range;

			if (m_UsedDefaultThreshold)
				SetViewingThreshold(50, range);
			else
				SetViewingThreshold(m_MinThreshold, range);
		}
#pragma endregion Bone Viewing

		break;
	case misVolumeViewingTypes::misAnimalViewing:
	
		switch (m_ImageModality)
		{
		case CT:
			double minThreshold;
			if (m_UsedDefaultThreshold)
			{
				minThreshold = -600;
				range = 450;
			}
			else
			{
				minThreshold = m_MinThreshold;
				// the min threshold for skin must be minus surely
				if (m_MinThreshold > -150)
					m_MinThreshold = -150;
				range = -150 - minThreshold;
				if (range > 400)
				{
					range = 400;
				}
				if (range < 100)
					range = 100;
			}

			SetViewingThreshold(minThreshold, range);
			break;

		case SPECT:

			if (-1 == m_Range)
				range = 500;
			else
				range = m_Range;

			if (m_UsedDefaultThreshold)
				SetViewingThreshold(900, range);
			else
				SetViewingThreshold(m_MinThreshold, range);
			break;

		case MRI:

			if (-1 == m_Range)
				range = 500;
			else
				range = m_Range;

			if (m_UsedDefaultThreshold)
				SetViewingThreshold(900, range);
			else
				SetViewingThreshold(m_MinThreshold, range);
			break;

		}
	}
}

void misAnimalVolumeColormaps::SetViewingThreshold(double minThreshold, double viewingRange)
{
	m_MinThreshold = minThreshold;
	if (viewingRange < 1) // the range must be atleast 1
	{
		viewingRange = 1;
	}

	m_MaxThreshold = m_MinThreshold + viewingRange;
}

void misAnimalVolumeColormaps::UpdateCTList(void)
{
	switch (m_VolumeType)
	{

	case misVolumeViewingTypes::misBoneViwing:
	{
		UpdateCTBoneList();
		break;
	}
	case misVolumeViewingTypes::misSkinFilledViewing:
	case misVolumeViewingTypes::misSkinviewing:
	case misVolumeViewingTypes::misAnimalViewing:
	{
		UpdateColorTFIList();
		break;
	}
	}
}

void misAnimalVolumeColormaps::UpdateCTAllList(void)
{
	misColorStruct        rawColor;
	if (!m_UseDefaultColor)
	{
		rawColor = m_ObjectColor;
	}
	else
	{
		rawColor.red = 250;
		rawColor.green = 220;
		rawColor.blue = 160;

		m_ObjectColor = rawColor;
	}

	rawColor.alpha = 0.0;
	m_ColorList[m_MinThreshold - 1] = rawColor;
	//***************------------------------------
	rawColor.alpha = 0.1;
	m_ColorList[m_MinThreshold] = rawColor;
	//***************------------------------------
	//rawColor = ChangeColor(rawColor, 10, 10, 10);
	//rawColor.alpha = 0.6;
	//m_ColorList[m_MinThreshold+14] = rawColor;
	//***************------------------------------
	rawColor = ChangeColor(rawColor, 10, 10, 10);
	rawColor.alpha = 1.0;
	m_ColorList[m_MinThreshold + 200] = rawColor;
	//***************------------------------------

	rawColor = ChangeColor(rawColor, 10, 10, 10);
	rawColor.alpha = 1.0;
	m_ColorList[150] = rawColor;
	///////////////   bony parts
	rawColor.red = 229;
	rawColor.green = 40;
	rawColor.blue = 20;
	m_ColorList[225] = rawColor;

	rawColor.red = 240;
	rawColor.green = 240;
	rawColor.blue = 240;
	m_ColorList[400] = rawColor;

	rawColor.red = 255;
	rawColor.green = 255;
	rawColor.blue = 255;
	m_ColorList[3500] = rawColor;

	rawColor.alpha = 0.0;
	m_ColorList[3500 + 1] = rawColor;

}

void misAnimalVolumeColormaps::UpdateColorTFIList()
{
	std::string		tfiFileName;
	if (m_ImageModality == SPECT)
		tfiFileName = m_TFIAddMap->GetTFIFileName(SPECT, misVolumeViewingTypes::misAnimalViewing);
	else if (m_ImageModality == CT)
		tfiFileName = m_TFIAddMap->GetTFIFileName(CT, misVolumeViewingTypes::misAnimalViewing);
	else if (m_ImageModality == MRI)
		tfiFileName = m_TFIAddMap->GetTFIFileName(MRI, misVolumeViewingTypes::misAnimalViewing);
	m_ColorList = m_TFILoader->LoadTFI(tfiFileName);

	if (m_UsedDefaultThreshold)
		return;

}

void misAnimalVolumeColormaps::UpdateCTSkinList(void)
{
	misColorStruct        rawColor;
	if (!m_UseDefaultColor)
		rawColor = m_ObjectColor;
	else
	{
		rawColor.red = 250;
		rawColor.green = 220;
		rawColor.blue = 160;

		m_ObjectColor = rawColor;
	}

	rawColor.alpha = 0.0;
	m_ColorList[m_MinThreshold - 1] = rawColor;
	//***************------------------------------
	rawColor.alpha = 0.1;
	m_ColorList[m_MinThreshold] = rawColor;
	//***************------------------------------
	//rawColor = ChangeColor(rawColor, 10, 10, 10);
	//rawColor.alpha = 0.6;
	//m_ColorList[m_MinThreshold+14] = rawColor;
	//***************------------------------------
	rawColor = ChangeColor(rawColor, 10, 10, 10);
	rawColor.alpha = 1.0;
	double val = m_MinThreshold + 200;
	if (val > m_MaxThreshold)
	{
		val = (m_MinThreshold + m_MaxThreshold) / 2;
	}
	m_ColorList[val] = rawColor;
	//***************------------------------------

	rawColor = ChangeColor(rawColor, 10, 10, 10);
	rawColor.alpha = 1.0;

	// display metal with diff color
	if (m_MaxThreshold - m_MinThreshold > 3000)
	{
		rawColor.red = 240;
		rawColor.green = 240;
		rawColor.blue = 240;
		m_ColorList[2900] = rawColor;

		rawColor = ChangeColor(rawColor, 255, 255, 255);
		m_ColorList[3500] = rawColor;
	}
	else
	{
		m_ColorList[m_MaxThreshold] = rawColor;
	}

	rawColor.alpha = 0.0;
	m_ColorList[m_MaxThreshold + 1] = rawColor;
}

void misAnimalVolumeColormaps::UpdateCTBoneList(void)
{

	misColorStruct   rawColor;
	if (m_UseDefaultColor)
	{
		// start with red color

		rawColor.red = 229;
		rawColor.green = 40;
		rawColor.blue = 20;
		rawColor.alpha = 0.0;
		m_ColorList[m_MinThreshold - 1] = rawColor;
		//  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
		// 		rawColor.red   = 229;
		// 		rawColor.green =203;//80;//157
		// 		rawColor.blue  = 138;//60;// 120
		rawColor.alpha = 0.2;
		m_ColorList[m_MinThreshold] = rawColor;
		//  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
		rawColor.red = 229;
		rawColor.green = 203;//203;//157
		rawColor.blue = 138;//138;// 120
		rawColor.alpha = 1.0;
		m_ColorList[m_MinThreshold + 100] = rawColor;
		//  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
		rawColor.red = 229;
		rawColor.green = 203;
		rawColor.blue = 138;
		//	m_ObjectColor = rawColor;
		rawColor.alpha = 1.0;
		m_ColorList[m_MinThreshold + 269] = rawColor;
		//  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~	
		rawColor = ChangeColor(rawColor, 25, 20, 5);
		rawColor.alpha = 1.0;
		m_ColorList[m_MaxThreshold] = rawColor;
		//  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
		rawColor.alpha = 0;
		m_ColorList[m_MaxThreshold + 1] = rawColor;

	}
	else
	{
		rawColor = m_ObjectColor;

		// 		rawColor.red   = 229;
		// 		rawColor.green = 40;
		// 		rawColor.blue  = 20;
		rawColor.alpha = 0.0;
		m_ColorList[m_MinThreshold - 1] = rawColor;
		//  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
		// 		rawColor.red   = 229;
		// 		rawColor.green = 80;//157
		// 		rawColor.blue  = 60;// 120
		rawColor.alpha = 0.2;
		m_ColorList[m_MinThreshold] = rawColor;
		//  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
		rawColor.red = 229;
		rawColor.green = 203;//157
		rawColor.blue = 138;// 120
		rawColor.alpha = 1.0;
		m_ColorList[m_MinThreshold + 100] = rawColor;
		//  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
		rawColor.red = 229;
		rawColor.green = 203;
		rawColor.blue = 138;
		rawColor.alpha = 1.0;
		m_ColorList[m_MinThreshold + 269] = rawColor;
		//  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~	
		rawColor = ChangeColor(rawColor, 25, 20, 5);
		rawColor.alpha = 1.0;
		m_ColorList[m_MaxThreshold] = rawColor;
		//  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
		rawColor.alpha = 0;
		m_ColorList[m_MaxThreshold + 1] = rawColor;
	}

}

void misAnimalVolumeColormaps::UpdateMRSkinList(void)
{
	misColorStruct   rawColor;

	if (!m_UseDefaultColor)
	{
		rawColor = m_ObjectColor;
	}
	else
	{
		rawColor.red = 250;
		rawColor.green = 220;
		rawColor.blue = 160;

		m_ObjectColor = rawColor;
	}

	//***************------------------------------
	rawColor.alpha = 0.0;
	m_ColorList[m_MinThreshold - 1] = rawColor;
	//***************------------------------------
	rawColor.alpha = 0.2;
	m_ColorList[m_MinThreshold] = rawColor;
	//***************------------------------------
	rawColor.alpha = 0.8;
	m_ColorList[m_MinThreshold + 14] = rawColor;
	//***************------------------------------
	rawColor = ChangeColor(rawColor, 10, 10, 0);
	rawColor.alpha = 1.0;
	m_ColorList[m_MinThreshold + 22] = rawColor;
	//***************------------------------------
	rawColor = ChangeColor(rawColor, 10, 10, 10);
	if (m_MaxThreshold > (m_MinThreshold + 1000))
	{
		rawColor.red = 255;
		rawColor.green = 255;
		rawColor.blue = 200;
	}
	rawColor.alpha = 1.0;
	m_ColorList[m_MaxThreshold] = rawColor;
	//***************------------------------------
	rawColor.alpha = 0.0;
	m_ColorList[m_MaxThreshold + 1] = rawColor;
}

misColorStruct misAnimalVolumeColormaps::ChangeColor(misColorStruct currentColor, int addRed, int addGreen, int addBlue)
{
	misColorStruct outColor;
	outColor = currentColor;

	outColor.red = currentColor.red + addRed;
	outColor.green = currentColor.green + addGreen;
	outColor.blue = currentColor.blue + addBlue;

	if (currentColor.red + addRed > 255)
		outColor.red = 255;
	else if (currentColor.red + addRed < 0)
		outColor.red = 0;

	if (currentColor.green + addGreen > 255)
		outColor.green = 255;
	else if (currentColor.green + addGreen < 0)
		outColor.green = 0;

	if (currentColor.blue + addBlue > 255)
		outColor.blue = 255;
	else if (currentColor.blue + addBlue < 0)
		outColor.blue = 0;

	return outColor;
}

void misAnimalVolumeColormaps::SetObjectColorDefault(void)
{
	m_UseDefaultColor = true;
}

misColorStruct misAnimalVolumeColormaps::GetObjectColor(void)
{
	return m_ObjectColor;
}

