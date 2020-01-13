#pragma once
#include "IImageCorrelationInitialTransformMatrixCreator.h"

namespace parcast
{

	class ImageCorrelationInitialTransformMatrixCreator : public IImageCorrelationInitialTransformMatrixCreator
	{
	public:
		vtkSmartPointer<vtkTransform>
			Create(std::shared_ptr<IImage> fixedImage, std::shared_ptr<IImage> movingImage) const
			override;
	};

}