#pragma once

#include "IDatasetIoWrapper.h"

namespace parcast
{
	
	MOCK_BASE_CLASS(MockDatasetIoWrapper, IDatasetIoWrapper)
	{
		MOCK_CONST_METHOD(ReadRawImage, 3, bool(const std::string& completeFileNameAddress,
			const misImageIOProperties& imageIOProperties, vtkImageData* image));

		MOCK_CONST_METHOD(SaveRawImage, 3, misResultCode::ResultIds(vtkImageData* spVtkImage,
			const std::string& address, const std::string& fileName));
	};

}
