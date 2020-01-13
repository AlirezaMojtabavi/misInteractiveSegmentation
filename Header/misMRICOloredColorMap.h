#pragma once
#include "misColorStruct.h"
#include "IMRIColoredColorMap.h"
#include "ITFIAddressMapper.h"
#include "ITFILoader.h"

// these color map keys copied from 3d Slicer MRIT2 color map
class misMRIColoredColorMap :public IMRIColoredColorMap
{
public:
	misMRIColoredColorMap(std::shared_ptr<ITFIAddressMapper> tFIAddMap,
		std::shared_ptr<ITFILoader> tfiLoader, 
		misVolumeViewingTypes volumeViewing);
	misMRIColoredColorMap(double minThreshold, double maxThreshold);
	misColorListTypedef GetColorList() const;
	 
private:
	std::shared_ptr<ITFIAddressMapper> m_TFIAddMap;
	std::shared_ptr<ITFILoader> m_TfiLoader;
	misColorListTypedef m_ColorList;
};

