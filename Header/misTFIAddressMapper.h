#pragma once
#include "ITFIAddressMapper.h"

class misTFIAddressMapper : public ITFIAddressMapper
{
public:
	// Creates a misTFIAddressMapper and fills it with default mappings for different modalities and viewing types.
	misTFIAddressMapper();

	virtual void SetTFIFileName(
		misImageDataModality modality, misVolumeViewingTypes viewingType, const std::string& fileName) override;
	virtual std::string GetTFIFileName(misImageDataModality modality, misVolumeViewingTypes viewingType) const override;

private:
	const std::string DefaultPath;
	// it is a map of image modalities such as CT, MRI, etc to a map of viewing to the string which is a name and 
	// address of a TFI file. this file is an xml that contains color keys for 3D a volume. 
	std::map<misImageDataModality, std::map<misVolumeViewingTypes, std::string>> m_FileNameList;
};