#pragma once
#include "misObject.h"
#include "misitkImageTypedef.h"



class   CommandIterationUpdate : public itk::Command
{
public:
  typedef  CommandIterationUpdate   Self;
  typedef  itk::Command             Superclass;
  typedef itk::SmartPointer<Self>  Pointer;
  int check;
  itkNewMacro( Self );
protected:
  CommandIterationUpdate()
  {
	  check=0;
  };
public:
  typedef itk::VersorRigid3DTransformOptimizer     OptimizerType;
  typedef     OptimizerType   *    OptimizerPointer;

  void Execute(itk::Object *caller, const itk::EventObject & event)
    {
		OptimizerPointer optimizer =
        dynamic_cast<  itk::VersorRigid3DTransformOptimizer  * >( caller );
		/*optimizer->StopOptimization();*/
		  if( ! itk::IterationEvent().CheckEvent( &event ) )
			{
			return;
		  }
    }

  void Execute(const itk::Object * object, const itk::EventObject & event)
    {
    }
};

class misCorrelation : public misObject
{
public:
	misCorrelation()
		 {
			 Dimension=3;
		 }

	public:
	igstkStandardClassBasicTraitsMacro( misCorrelation, misObject)
		itkNewMacro(misCorrelation);
	unsigned int    Dimension  ;

	typedef misitkImageType  FixedImageType;
	typedef misitkImageType  MovingImageType;
	typedef misitkImageType  OutputImageType;

	typedef itk::CastImageFilter<
							FixedImageType,OutputImageType > CastFilterType;
	typedef itk::VersorRigid3DTransform< double > TransformType;
	typedef itk::VersorRigid3DTransformOptimizer           OptimizerType;
	typedef itk::MattesMutualInformationImageToImageMetric<
										FixedImageType,
										MovingImageType >    MetricType;
	typedef itk:: LinearInterpolateImageFunction<
										MovingImageType,
										double          >    InterpolatorType;
	typedef itk::ImageRegistrationMethod<
										FixedImageType,
										MovingImageType >    RegistrationType;

 	typedef itk::CenteredTransformInitializer< TransformType,
												 FixedImageType,
												 MovingImageType
													 >  TransformInitializerType;
	typedef TransformType::VersorType  VersorType;
	typedef VersorType::VectorType     VectorType;
	typedef OptimizerType::ScalesType       OptimizerScalesType;
	typedef itk::ResampleImageFilter<
								MovingImageType,
								FixedImageType >    ResampleFilterType;
		typedef itk::SubtractImageFilter<
									  FixedImageType,
									  FixedImageType,
									  FixedImageType > DifferenceFilterType;
	typedef itk::RescaleIntensityImageFilter<
									  FixedImageType,
									  OutputImageType >   RescalerType;
	typedef itk::IdentityTransform< double, 3 > IdentityTransformType;
	typedef itk::Image< misitkPixelType, 2 > OutputSliceType;

	  typedef itk::ExtractImageFilter<
							  OutputImageType,
							  OutputSliceType > ExtractFilterType;
	CastFilterType::Pointer  caster;

	itk::Image< float , 3 >* StartCorrelation(itk::Image< float , 3 >* pFixedImage ,itk::Image< float , 3 >* pMovingImage);
};

