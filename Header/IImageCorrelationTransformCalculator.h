#pragma once
#include "IImage.h"

namespace parcast
{

	class IImageCorrelationTransformMatrixCalculator
	{
	public:
		virtual void Create(
			std::shared_ptr<IImage> fixedImage,
			std::shared_ptr<IImage> movingImage,
			vtkSmartPointer<vtkMatrix4x4> result) const = 0;
	};

}
