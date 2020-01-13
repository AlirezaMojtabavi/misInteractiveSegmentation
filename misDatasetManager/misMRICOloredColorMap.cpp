#include "stdafx.h"
#include "..\Header\misMRICOloredColorMap.h"
#include "misTFILoader.h"


misMRIColoredColorMap::misMRIColoredColorMap(std::shared_ptr<ITFIAddressMapper> tFIAddMap, 
	std::shared_ptr<ITFILoader> tfiLoader, misVolumeViewingTypes volumeViewing)
	:m_TFIAddMap(tFIAddMap), m_TfiLoader(tfiLoader)
{

	m_ColorList = m_TfiLoader->LoadTFI(m_TFIAddMap->GetTFIFileName(MRI, volumeViewing));
}

misMRIColoredColorMap::misMRIColoredColorMap(double minThreshold, double maxThreshold)
 {
	double range = maxThreshold - minThreshold;
	m_ColorList[0.0] = misColorStruct(0, 0, 0, 0);
	m_ColorList[minThreshold + range * 0.08] = misColorStruct(0, 0, 0, 0);
	m_ColorList[minThreshold + range * 0.16] = misColorStruct(244, 214, 49, 15);
	m_ColorList[minThreshold + range * 0.3] = misColorStruct(158, 197, 104, 51);
	m_ColorList[minThreshold + range * 0.6] = misColorStruct(0, 151, 206, 255);
	m_ColorList[maxThreshold] = misColorStruct(255, 255, 255, 255);

}

misColorListTypedef misMRIColoredColorMap::GetColorList() const
{
	return m_ColorList;
}

