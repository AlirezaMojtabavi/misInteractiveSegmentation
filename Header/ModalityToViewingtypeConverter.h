#pragma once
#include "misEnums.h"
#include "misImageModalityEnum.h"
#include "misobjectProperitiesEnums.h"
#include "misVolumeViewingTypes.h"

class ModalityToViewingtypeConverter
{
public:
	ModalityToViewingtypeConverter(misImageDataModality modality, misApplicationType appType);
	~ModalityToViewingtypeConverter();

	misVolumeViewingTypes GetDefultVolumeViewingType();

private:
	misApplicationType m_AppType;
	misImageDataModality m_Modality;
};

