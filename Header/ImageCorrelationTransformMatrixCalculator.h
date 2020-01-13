#pragma once
#include "IImageCorrelationTransformCalculator.h"
#include "ICoordinateSystemCorrelationManager.h"
#include "IImageCorrelationInitialTransformMatrixCreator.h"

namespace parcast
{

	class ImageCorrelationTransformMatrixCalculator : public IImageCorrelationTransformMatrixCalculator
	{
	public:
		ImageCorrelationTransformMatrixCalculator(
			std::weak_ptr<ICoordinateSystemCorrelationManager<std::string>> correlationManager,
			std::shared_ptr<IImageCorrelationInitialTransformMatrixCreator> imageCorrelationInitialTransformMatrixCreator);
		void Create(
			std::shared_ptr<IImage> fixedImage,
			std::shared_ptr<IImage> movingImage,
			vtkSmartPointer<vtkMatrix4x4> result) const override;

	private:
		std::weak_ptr<ICoordinateSystemCorrelationManager<std::string>> m_CorrelationManager;
		std::shared_ptr<IImageCorrelationInitialTransformMatrixCreator> m_ImageCorrelationInitialTransformMatrixCreator;
	};

}
