#include "stdafx.h"
#include "ModalityToViewingtypeConverter.h"

ModalityToViewingtypeConverter::ModalityToViewingtypeConverter(misImageDataModality modality, misApplicationType appType)
	: m_Modality(modality), 
	m_AppType(appType)
{  
}

ModalityToViewingtypeConverter::~ModalityToViewingtypeConverter()
{
}

misVolumeViewingTypes ModalityToViewingtypeConverter::GetDefultVolumeViewingType()
{
	if (m_AppType == Spine)
	{
		if (m_Modality == CT)
			return misVolumeViewingTypes::misSpineViewing;
		return misVolumeViewingTypes::misSkinviewing;
	}
	if (m_AppType == Dental)
		return misVolumeViewingTypes::misTeethViewing;
	if (m_AppType == AnimalImaging)
		return misVolumeViewingTypes::misAnimalViewing;
	return misVolumeViewingTypes::misSkinFilledViewing;
}