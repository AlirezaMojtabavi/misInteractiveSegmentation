#include "stdafx.h"
#include "DatasetIoWrapper.h"

#include "misDatasetIO.h"

using namespace parcast;

bool DatasetIoWrapper::ReadRawImage(const std::string& completeFileNameAddress,
	const misImageIOProperties& imageIOProperties, vtkImageData* image) const
{
	return misDatasetIO::ReadRawImage(completeFileNameAddress, imageIOProperties, image);
}

misResultCode::ResultIds DatasetIoWrapper::SaveRawImage(vtkImageData* image,
	const std::string& address, const std::string& fileName) const
{
	if (!boost::filesystem::exists(address))
		boost::filesystem::create_directory(address);

	auto fullPath = boost::filesystem::path(address) / boost::filesystem::path(fileName);
	return misDatasetIO::SaveRaWImage(image, fullPath.string());
}