#include "stdafx.h"

#include "DentalVolumeColormaps.h"
#include "misAnimalVolumeColormaps.h"
#include "misApplicationSetting.h"
#include "misColormapGeneratorFactory.h"
#include "misVolumeRenderingColorMaps.h"


misColormapGeneratorFactory::misColormapGeneratorFactory()
{
	m_ColormapTypes[AnimalImagingColormap] = std::make_unique<misAnimalVolumeColormaps>(misApplicationSetting::GetInstance()->GetTFIAddressMap());
	m_ColormapTypes[DentalColormap] = std::make_unique<DentalVolumeColormaps>(misApplicationSetting::GetInstance()->GetTFIAddressMap());
	m_ColormapTypes[OtherColormap] = std::make_unique<misVolumeRenderingColorMaps>(misApplicationSetting::GetInstance()->GetTFIAddressMap());

}

std::unique_ptr<IVolumeRenderingColorMaps> misColormapGeneratorFactory::createColormapType(ColormapTypes cmapType)
{
	return m_ColormapTypes[cmapType]->clone();
}