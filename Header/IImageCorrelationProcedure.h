#pragma once
#include "LevelInformation.h"
#include "RecursivePyramidFilter.h"

class ImageCorrelationSetting;

namespace parcast
{

	class IImageCorrelationProcedure
	{
	public:
		virtual ~IImageCorrelationProcedure() = default;

		virtual itk::Rigid3DTransform<double>::Pointer StartCorrelation(
			itk::RecursivePyramidFilter<itk::Image<float, 3 >, itk::Image<float, 3 >>::Pointer fixedPyramid,
			itk::RecursivePyramidFilter<itk::Image<float, 3 >, itk::Image<float, 3 >>::Pointer movingPyramid,
			vector<itk::Image<float, 3 >::RegionType> pyramidRegion,
			vtkSmartPointer<vtkMatrix4x4> transformMatrix,
			HANDLE pyramidMutex) = 0;
		virtual void SetImageCorrelationSetting(const ImageCorrelationSetting& imageCorrelationSetting) = 0;
		virtual void Initialize(int numberOfLevel, const std::vector<levelInformation>& levelInfo) = 0;
		virtual void StopCorrelation() = 0;
		virtual void WaitUntilRegistrationFinished() = 0;
		virtual vtkSmartPointer<vtkMatrix4x4> GetCurrentTransformMatrix() = 0;
		virtual double CalculateProgressBarValue(bool resetCorrelation) = 0;
		virtual bool IsMultiResCorrelationNull() const = 0;
	};

}
