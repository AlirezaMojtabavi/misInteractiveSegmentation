#pragma once

#include "ITFIAddressMapper.h"

MOCK_BASE_CLASS(MockTFIAddressMapper, ITFIAddressMapper)
{
	MOCK_NON_CONST_METHOD(SetTFIFileName, 3, void (misImageDataModality modality, misVolumeViewingTypes viewingType,
		const std::string& fileName));
	MOCK_CONST_METHOD(GetTFIFileName, 2, std::string (misImageDataModality modality, misVolumeViewingTypes viewingType));
};