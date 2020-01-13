#pragma once
#include "IImage.h"

namespace parcast
{

	class IImageCorrelationInitialTransformMatrixCreator
	{
	public:
		virtual vtkSmartPointer<vtkTransform> Create(
			std::shared_ptr<IImage> fixedImage,
			std::shared_ptr<IImage> movingImage) const = 0;
	};

}
