#include "stdafx.h"

#include "DentalVolumeColormaps.h"
#include "ITFIAddressMapper.h"
#include "ITFILoader.h"
#include "misColorStruct.h"
#include "misTFILoader.h"




DentalVolumeColormaps::DentalVolumeColormaps(std::shared_ptr<ITFIAddressMapper> tfiMap)
	:m_TFILoader(std::make_shared<misTFILoader>()), m_TFIAddMap(tfiMap)
{

}

DentalVolumeColormaps::DentalVolumeColormaps(std::shared_ptr<ITFIAddressMapper> tfiMap, std::shared_ptr<ITFILoader> TFILoader)
	:
	m_TFIAddMap(tfiMap), m_TFILoader(TFILoader)
{

}





misColorListTypedef DentalVolumeColormaps::GetVolumeColorMap()
{
	m_ColorList.clear();
	UpdateThresholds();
	UpdateColorTFIList();
	return m_ColorList;
}

std::unique_ptr<IVolumeRenderingColorMaps> DentalVolumeColormaps::clone()
{
	return std::make_unique<DentalVolumeColormaps>(*this);
}

void DentalVolumeColormaps::SetImageModality(misImageDataModality imageModality)
{
	m_ImageModality = imageModality;
}

void DentalVolumeColormaps::SetObjectType(misVolumeViewingTypes volumeType)
{
	m_VolumeType = volumeType;
}

void DentalVolumeColormaps::SetObjectThreshold(double minThreshold)
{
	m_MinThreshold = minThreshold;
	m_Range = -1;

	m_UsedDefaultThreshold = false;
}



void DentalVolumeColormaps::SetObjectThresholdDefault(void)
{
	m_Range = -1;
	m_UsedDefaultThreshold = true;
}

void DentalVolumeColormaps::SetObjectColorDefault(void)
{
	m_UseDefaultColor = true;
}

misColorStruct DentalVolumeColormaps::GetObjectColor(void)
{
	auto colorStrc = misColorStruct(0, 0, 0, 0);
	return colorStrc;
}

void DentalVolumeColormaps::UpdateColorTFIList()
{
	auto tfiFileName = m_TFIAddMap->GetTFIFileName(CT, m_VolumeType);
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

void DentalVolumeColormaps::UpdateThresholds(void)
{
	double range;
	switch (m_VolumeType)
	{
	case misVolumeViewingTypes::misTeethViewing:
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
			break;
		}
#pragma endregion Bone Viewing
	case misVolumeViewingTypes::misTeethSolidViewing:
	{
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
			break;
		}
	}
	}
}

void DentalVolumeColormaps::SetViewingThreshold(double minThreshold, double viewingRange)
{
	m_MinThreshold = minThreshold;
	if (viewingRange < 1) // the range must be atleast 1
	{
		viewingRange = 1;
	}
	m_MaxThreshold = m_MinThreshold + viewingRange;
}

