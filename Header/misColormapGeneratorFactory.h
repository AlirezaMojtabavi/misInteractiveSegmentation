#pragma once
#include "IVolumeRenderingColorMaps.h"
#include "misEnums.h"
class misColormapGeneratorFactory
{
public:
	misColormapGeneratorFactory();
	std::unique_ptr<IVolumeRenderingColorMaps> createColormapType(ColormapTypes cmapType);

private:
	std::unordered_map<ColormapTypes, std::unique_ptr<IVolumeRenderingColorMaps>> m_ColormapTypes;

};
