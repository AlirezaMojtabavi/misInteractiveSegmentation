#pragma once

#include "misResultCode.h"
#include "misImageIOProperties.h"

namespace parcast
{
	
	class IDatasetIoWrapper
	{
	public:
		virtual bool ReadRawImage(const std::string& completeFileNameAddress,
			const misImageIOProperties& imageIOProperties, vtkImageData* image) const = 0;

		 virtual misResultCode::ResultIds SaveRawImage(vtkImageData* spVtkImage,
			 const std::string& address, const std::string& fileName) const = 0;
	};

}
