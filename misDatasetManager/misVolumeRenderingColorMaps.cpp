#include "StdAfx.h"
#include "misVolumeRenderingColorMaps.h"

#include "misTFILoader.h"
#include "misTFIAddressMapper.h"
#include "misobjectProperitiesEnums.h"
#include "misMRICOloredColorMap.h"
#include "IMRIColoredColorMap.h"
#include "ColorMapBoneCT.h"
#include "CTSkinFilledColorMap.h"
#include "MRSkinFilledColorMap.h"
#include "CTSkinTransparentColorMap.h"
#include "MRSkinTransparentColorMap.h"
#include "CTAllViewingColormap.h"
#include "MRAllViewingColorMap.h"
#include "CTSinusViewingColorMap.h"
#include "MRSinusViewingColorMap.h"
#include "misVolumeViewingTypes.h"


misVolumeRenderingColorMaps::misVolumeRenderingColorMaps(std::shared_ptr<ITFIAddressMapper> tfiMap)
	: m_TFILoader(std::make_shared<misTFILoader>()),
	m_TFIAddMap(tfiMap),
	m_BoneCTColormap(std::make_shared<ColorMapBoneCT>(0, 0)),
	m_CTSkinFilledColorMap(std::make_shared<CTSkinFilledColorMap>(0, 0)),
	m_MRSkinFilledColorMap(std::make_shared<MRSkinFilledColorMap>(m_TFIAddMap, m_TFILoader)),
	m_CTSkinTransparentColorMap(std::make_shared<CTSkinTransparentColorMap>(0, 0)),
	m_MRSkinTransparentColorMap(std::make_shared<MRSkinTransparentColorMap>(m_TFIAddMap, m_TFILoader)),
	m_CTAllViewingColorMap(std::make_shared<ctAllViewingColormap>(0, 0)),
	m_MRAllViewingColorMap(std::make_shared<mrAllViewingColorMap>(m_TFIAddMap, m_TFILoader)),
	m_CTSinusViewingColorMap(std::make_shared<CTSinusViewingColorMap>())
	, m_MRSinusViewingColorMap(std::make_shared<MRSinusViewingColorMap>(m_TFIAddMap, m_TFILoader))
{
}

misVolumeRenderingColorMaps::misVolumeRenderingColorMaps(std::shared_ptr<ITFIAddressMapper> tfiMap,
	std::shared_ptr<ITFILoader> tfiLoader)
	: m_TFIAddMap(tfiMap),
	m_TFILoader(tfiLoader),
	m_BoneCTColormap(std::make_shared<ColorMapBoneCT>(0, 0)),
	m_CTSkinFilledColorMap(std::make_shared<CTSkinFilledColorMap>(0, 0)),
	m_MRSkinFilledColorMap(std::make_shared<MRSkinFilledColorMap>(m_TFIAddMap, m_TFILoader))
	, m_CTSkinTransparentColorMap(std::make_shared<CTSkinTransparentColorMap>(0, 0))
	, m_MRSkinTransparentColorMap(std::make_shared<MRSkinTransparentColorMap>(m_TFIAddMap, m_TFILoader))
	, m_CTAllViewingColorMap(std::make_shared<ctAllViewingColormap>(0, 0)),
	m_MRAllViewingColorMap(std::make_shared<mrAllViewingColorMap>(m_TFIAddMap, m_TFILoader)),
	m_CTSinusViewingColorMap(std::make_shared<CTSinusViewingColorMap>())
	, m_MRSinusViewingColorMap(std::make_shared<MRSinusViewingColorMap>(m_TFIAddMap, m_TFILoader))

{
}




misColorListTypedef misVolumeRenderingColorMaps::GetVolumeColorMap()
{
	m_ColorList.clear();
	UpdateThresholds();
	UpdateColorList();
	return m_ColorList;
}

std::unique_ptr<IVolumeRenderingColorMaps> misVolumeRenderingColorMaps::clone()
{
	return std::make_unique<misVolumeRenderingColorMaps>(*this);
}

void misVolumeRenderingColorMaps::SetObjectColor(const misColorStruct& objectColor)
{
	m_ObjectColor = objectColor;
	m_UseDefaultColor = false;
}

void misVolumeRenderingColorMaps::SetObjectThreshold(double minThreshold)
{
	m_MinThreshold = minThreshold;
	m_UsedDefaultThreshold = false;
	m_BoneCTColormap->SetMinThreshold(m_MinThreshold);
	m_CTSkinFilledColorMap->SetMinThreshold(m_MinThreshold);
	m_MRSkinFilledColorMap->SetMinThreshold(m_MinThreshold);
	m_CTSkinTransparentColorMap->SetMinThreshold(m_MinThreshold);
	m_MRSkinTransparentColorMap->SetMinThreshold(m_MinThreshold);
}

double misVolumeRenderingColorMaps::GetObjectThreshold()
{
	return m_MinThreshold;
}

void misVolumeRenderingColorMaps::SetObjectThresholdDefault(void)
{
	m_UsedDefaultThreshold = true;
}


void misVolumeRenderingColorMaps::SetImageModality(misImageDataModality imageModality)
{
	m_UsedDefaultThreshold = true;
	m_ImageModality = imageModality;

}

void misVolumeRenderingColorMaps::SetObjectType(misVolumeViewingTypes volumeType)
{
	m_VolumeType = volumeType;
}

void misVolumeRenderingColorMaps::UpdateColorList(void)
{
	if (m_ImageModality == MRI)
	{
		UpdateMRList();
		return;
	}
	UpdateCTList();

}



void misVolumeRenderingColorMaps::UpdateThresholds(void)
{
	double range;
	switch (m_VolumeType)
	{
	case misVolumeViewingTypes::misSkinFilledViewing:
	{
#pragma region skin filled Viewing
		switch (m_ImageModality)
		{
		case CT:

			m_CTSkinFilledColorMap->SetViewingThreshold(m_UsedDefaultThreshold, m_MinThreshold);
			break;

		case MRI:
			m_MRSkinFilledColorMap->SetViewingThreshold(m_UsedDefaultThreshold, m_MinThreshold);
			break;

		default:
			cout << " \n    Unconsidered Image Modality \n";
			range = 3500;

			if (m_UsedDefaultThreshold)
				SetViewingThreshold(50, range);
			else
				SetViewingThreshold(m_MinThreshold, range);
			break;

		}
#pragma endregion skin Viewing
		break;
	}

	case misVolumeViewingTypes::misSkinviewing:
	{
#pragma region skin Viewing
		switch (m_ImageModality)
		{
		case CT:
			m_CTSkinTransparentColorMap->SetViewingThreshold(m_UsedDefaultThreshold, m_MinThreshold);
			break;

		case MRI:
			m_MRSkinTransparentColorMap->SetViewingThreshold(m_UsedDefaultThreshold, m_MinThreshold);
			break;

		}
#pragma endregion skin Viewing
		break;
	}

	case misVolumeViewingTypes::misBoneViwing:
	{
		m_BoneCTColormap->SetViewingThreshold(m_UsedDefaultThreshold, m_MinThreshold);
		break;
	}

	case misVolumeViewingTypes::misMetalViewing:
	{

		switch (m_ImageModality)
		{
		case CT:
			range = 3000;

			SetViewingThreshold(2750, range);
			break;
		}

		break;
	}

	case misVolumeViewingTypes::misAllViewing:
		m_CTAllViewingColorMap->SetViewingThreshold(m_UsedDefaultThreshold, m_MinThreshold);
		m_MRAllViewingColorMap->SetViewingThreshold(m_UsedDefaultThreshold, m_MinThreshold);
		break;

	case misVolumeViewingTypes::misSinusesViewing:
		m_CTSinusViewingColorMap->SetViewingThreshold(m_UsedDefaultThreshold, m_MinThreshold);
		m_MRAllViewingColorMap->SetViewingThreshold(m_UsedDefaultThreshold, m_MinThreshold);
		break;
	default:

		break;

	}
}


void misVolumeRenderingColorMaps::SetViewingThreshold(double minThreshold, double viewingRange)
{
	m_MinThreshold = minThreshold;
	if (viewingRange < 1) // the range must be atleast 1
	{
		viewingRange = 1;
	}

	m_MaxThreshold = m_MinThreshold + viewingRange;


}

void misVolumeRenderingColorMaps::UpdateCTList(void)
{
	switch (m_VolumeType)
	{
	case misVolumeViewingTypes::misSkinFilledViewing:
	{
		m_ColorList = m_CTSkinFilledColorMap->GetColorMap(m_UseDefaultColor, m_ObjectColor);
		break;
	}

	case misVolumeViewingTypes::misSkinviewing:
	{
		m_ColorList = m_CTSkinTransparentColorMap->GetColorMap(m_UseDefaultColor, m_ObjectColor);

		break;
	}

	case misVolumeViewingTypes::misBoneViwing:
	{
		m_ColorList = m_BoneCTColormap->GetColorMap(m_UseDefaultColor, m_ObjectColor);
		break;
	}

	case misVolumeViewingTypes::misSinusesViewing:
	{
		m_ColorList = m_CTSinusViewingColorMap->GetColorMap(m_UseDefaultColor, m_ObjectColor);
		break;
	}
	case misVolumeViewingTypes::misMetalViewing:
	{
		UpdateCTMetalList();
		break;
	}
	case misVolumeViewingTypes::misAllViewing:
	{
		m_ColorList = m_CTAllViewingColorMap->GetColorMap(m_UseDefaultColor, m_ObjectColor);

		break;
	}

	case misVolumeViewingTypes::misTeethViewing:
	case misVolumeViewingTypes::misSpineViewing:
	{
		UpdateColorTFIList(CT);
		break;
	}
	}
}

void misVolumeRenderingColorMaps::UpdateMRList(void)
{
	switch (m_VolumeType)
	{
	case misVolumeViewingTypes::misSkinFilledViewing:
	{
		m_ColorList = m_MRSkinFilledColorMap->GetColorMap(m_UseDefaultColor, m_ObjectColor);
		break;
	}
	case misVolumeViewingTypes::misSkinviewing:
	{
		m_ColorList = m_MRSkinTransparentColorMap->GetColorMap(m_UseDefaultColor, m_ObjectColor);
		break;
	}

	case misVolumeViewingTypes::misAllViewing:
	{
		m_ColorList = m_MRAllViewingColorMap->GetColorMap(m_UseDefaultColor, m_ObjectColor);
		break;
	}
	case misVolumeViewingTypes::misSinusesViewing:
	{
		m_ColorList = m_MRSinusViewingColorMap->GetColorMap(m_UseDefaultColor, m_ObjectColor);
		break;
	}
	default:
	{
		break;
	}
	}
}

void misVolumeRenderingColorMaps::UpdateCTMetalList(void)
{
	misColorStruct   rawColor;

	if (!m_UseDefaultColor)
	{
		rawColor = m_ObjectColor;
	}
	else
	{
		rawColor.red = 240;
		rawColor.green = 240;
		rawColor.blue = 240;

		m_ObjectColor = rawColor;
	}


	rawColor.alpha = 0.0;
	m_ColorList[m_MinThreshold - 1] = rawColor;

	rawColor.alpha = 0.2;
	m_ColorList[m_MinThreshold] = rawColor;

	rawColor.ChangeColor(10, 10, 10);
	rawColor.alpha = 1.0;
	m_ColorList[m_MinThreshold + 50] = rawColor;

	rawColor.ChangeColor(20, 20, 20);
	rawColor.alpha = 1;
	m_ColorList[m_MaxThreshold] = rawColor;
	//***************------------------------------
	rawColor.alpha = 0;
	m_ColorList[m_MaxThreshold + 1] = rawColor;
}

void misVolumeRenderingColorMaps::SetObjectColorDefault(void)
{
	m_UseDefaultColor = true;
}

misColorStruct misVolumeRenderingColorMaps::GetObjectColor(void)
{
	return m_ObjectColor;
}

void misVolumeRenderingColorMaps::UpdateColorTFIList(misImageDataModality modality)
{
	auto tfiFileName = m_TFIAddMap->GetTFIFileName(modality, m_VolumeType);
	m_ColorList = m_TFILoader->LoadTFI(tfiFileName);

	if (m_UsedDefaultThreshold)
		return;

	auto minIntensityDiff = std::abs(m_ColorList.begin()->first - m_MinThreshold);
	m_ColorList[m_MinThreshold] = m_ColorList.begin()->second;
	m_ColorList[m_MinThreshold].alpha = 0;
	for (auto itter = m_ColorList.begin(); itter != m_ColorList.end(); ++itter)
	{
		if (itter->first < m_MinThreshold)
			itter->second.alpha = 0;

		if (itter->first == m_MinThreshold)
			continue;

		if (std::abs(itter->first - m_MinThreshold) < minIntensityDiff)
		{
			m_ColorList[m_MinThreshold] = itter->second;
			m_ColorList[m_MinThreshold].alpha = 0;
			minIntensityDiff = std::abs(itter->first - m_MinThreshold);
		}
	}
}

