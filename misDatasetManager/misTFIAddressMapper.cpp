#include "stdafx.h"
#include "misTFIAddressMapper.h"

misTFIAddressMapper::misTFIAddressMapper()
	: DefaultPath("Resources\\transferfuncs\\dental.xml")
{
}

void misTFIAddressMapper::SetTFIFileName(
	misImageDataModality modality, misVolumeViewingTypes viewingType, const std::string& fileName)
{
	m_FileNameList[modality][viewingType] = fileName;
}

std::string misTFIAddressMapper::GetTFIFileName(misImageDataModality modality, misVolumeViewingTypes viewingType) const
{
	auto pathsForModality = m_FileNameList.find(modality);
	if (pathsForModality == m_FileNameList.cend())
		return DefaultPath;
	auto pathForViewingType = pathsForModality->second.find(viewingType);
	if (pathForViewingType == pathsForModality->second.cend())
		return DefaultPath;
	return pathForViewingType->second;
}