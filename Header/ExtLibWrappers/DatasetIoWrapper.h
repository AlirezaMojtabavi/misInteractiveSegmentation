#pragma once

#include "misResultCode.h"
#include "IDatasetIoWrapper.h"

namespace parcast
{

	class DatasetIoWrapper : public IDatasetIoWrapper
	{
	public:
		virtual bool ReadRawImage(const std::string& completeFileNameAddress,
			const misImageIOProperties& imageIOProperties, vtkImageData* image) const override;

		virtual misResultCode::ResultIds SaveRawImage(vtkImageData* spVtkImage,
			const std::string& address, const std::string& fileName)  const override;
	};

}
