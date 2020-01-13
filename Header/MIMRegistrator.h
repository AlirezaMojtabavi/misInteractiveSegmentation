/*=========================================================================

Program:   Insight Segmentation & Registration Toolkit
Module:    $RCSfile: MIMRegistrator.h,v $
Language:  C++
Date:      $Date: 2002-10-05 15:49:25 $
Version:   $Revision: 1.2 $

Copyright (c) 2002 Insight Consortium. All rights reserved.
See ITKCopyright.txt or http://www.itk.org/HTML/Copyright.htm for details.

This software is distributed WITHOUT ANY WARRANTY; without even
the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
PURPOSE.  See the above copyright notices for more information.

=========================================================================*/
#ifndef _MIMRegistrator_h
#define _MIMRegistrator_h


#include "CostValueInformation.h"
#include "RecursivePyramidFilter.h"
#include "misMultiResolutionImageRegistrationMethod.h"


namespace itk
{
	/** \class MIMRegistrator
	*
	* This component computes the transform to register a
	* moving image onto a fixed image.
	*
	* In particular, it uses the ITK registration framework with
	* the following combination of components:
	*   - MutualInformationImageToImageMetric
	*   - QuaternionRigidTransform
	*   - QuaternionRigidTransformGradientDescentOptimizer
	*   - LinearInterpolateImageFunction
	*
	* The registration is done using a multiresolution strategy.
	* At each resolution level, the downsampled images are obtained
	* using a RecursiveMultiResolutionPyramidImageFilter.
	*
	* \warning This class requires both images to be 3D and with
	* pixels of a real type.
	*
	* The registration process is activated by method Execute().
	*
	* Inputs:
	*   - pointer to fixed image
	*   - pointer to moving image
	*   - number of resolution levels
	*   - scaling applied to the translation parameters during optimization
	*   - parzen window width for the fixed image
	*   - parzen window width for the moving image
	*   - number of optimization iterations at each level
	*   - the optimization learning rate at each level
	*   - the initial rigid (quaternion) transform parameters
	*   - the coarest level shrink factors for the fixed image
	*   - the coarest level shrink factors for the moving image
	*
	* Outputs:
	*   - rigid (quaternion) transform parameters to maps points from
	*     the fixed image to the moving image.
	*   - pointer to equivalent affine transform.
	*
	*/
	template <typename TFixedImage, typename TMovingImage>
	class MIMRegistrator : public Object
	{
	public:
		 typedef typename TFixedImage::RegionType      FixedImageRegionType;
		/** Standard class typedefs. */
		typedef MIMRegistrator Self;
		typedef Object Superclass;
		typedef SmartPointer<Self> Pointer;
		typedef SmartPointer<const Self>  ConstPointer;

		/** Run-time type information (and related methods). */
		itkTypeMacro(MIMRegistrator, Object);

		/** Method for creation through the object factory. */
		itkNewMacro(Self);

		/** Fixed Image Type. */
		typedef TFixedImage FixedImageType;

		/** Moving Image Type. */
		typedef TMovingImage MovingImageType;

		/** Image dimension enumeration. */
		itkStaticConstMacro (ImageDimension, unsigned int, TFixedImage::ImageDimension);

		/** Transform Type. */
		typedef QuaternionRigidTransform< double >       TransformType;

		/** Optimizer Type. */
		typedef QuaternionRigidTransformGradientDescentOptimizer
			OptimizerType;

		/** Metric Type. */
		typedef MutualInformationImageToImageMetric<
			FixedImageType,
			MovingImageType >    MetricType;

		/** Interpolation Type. */
		typedef LinearInterpolateImageFunction<
			MovingImageType,
			double          >    InterpolatorType;

		/** Fixed Image Pyramid Type. */
		/* typedef RecursiveMultiResolutionPyramidImageFilter<
		FixedImageType,
		FixedImageType  >    FixedImagePyramidType;*/

		typedef RecursivePyramidFilter<
			FixedImageType,
			FixedImageType  >    FixedImagePyramidType;

		/** Moving Image Pyramid Type. */
		/*typedef RecursiveMultiResolutionPyramidImageFilter<
		MovingImageType,
		MovingImageType  >
		;*/

		typedef RecursivePyramidFilter<
			MovingImageType,
			MovingImageType  >    MovingImagePyramidType;

		/** Registration Method. */
		typedef misMultiResolutionImageRegistrationMethod<
			FixedImageType,
			MovingImageType >    RegistrationType;

		/** Transform parameters type. */
		typedef typename RegistrationType::ParametersType     ParametersType;

		/** DoubleArray type. */
		typedef Array<double>  DoubleArray;

		/** UnsignedIntArray type. */
		typedef Array<unsigned int> UnsignedIntArray;

		/** ShrinkFactorsArray type. */
		typedef itk::FixedArray<unsigned int,itkGetStaticConstMacro(ImageDimension)> ShrinkFactorsArray;

		typedef itk::Rigid3DTransform<double>   Rigid3DTransformType;
		typedef typename Rigid3DTransformType::Pointer Rigid3DTransformPointer;

		/** Set the fixed image. */
		itkSetObjectMacro( FixedImage, FixedImageType );

		/** Set the moving image. */
		itkSetObjectMacro( MovingImage, MovingImageType );

		/** Set the number of resolution levels. */
		itkSetClampMacro( NumberOfLevels, unsigned short, 1,
			NumericTraits<unsigned short>::max() );

		/** Set the translation parameter scales. */
		itkSetClampMacro( TranslationScale, double, 0.0,
			NumericTraits<double>::max() );

		/** Set the image parzen window widths. */
		itkSetClampMacro( MovingImageStandardDeviation, double, 0.0,
			NumericTraits<double>::max() );
		itkSetClampMacro( FixedImageStandardDeviation, double, 0.0,
			NumericTraits<double>::max() );

		/** Set the number of spatial samples. */
		itkSetClampMacro( NumberOfSpatialSamples, unsigned short, 1,
			NumericTraits<unsigned short>::max() );

		/** Set the number of iterations per level. */
		itkSetMacro( NumberOfIterations, UnsignedIntArray );

		/** Set the learning rate per level. */
		itkSetMacro( LearningRates, DoubleArray );

		/** Set the initial transform parameters. */
		itkSetMacro( InitialParameters, ParametersType );

		/** Set the fixed and moving image shrink factors. */
		itkSetMacro( FixedImageShrinkFactors, ShrinkFactorsArray );
		itkSetMacro( MovingImageShrinkFactors, ShrinkFactorsArray );

		/** Method to execute the registration. */
		virtual void Execute();

		/** Get number of parameters. */
		unsigned long GetNumberOfParameters()
		{ return m_Transform->GetNumberOfParameters(); }

		/** Get computed transform parameters. */
		const ParametersType& GetTransformParameters();

		/** Get computed affine transform. */
		Rigid3DTransformPointer GetCurrentTransformMatrix();

		/** Initialize registration at the start of new level. */
		void StartNewLevel();

		//RAMA
		void StartNewIteration();
		void set_m_stopOptimization(bool);
		void setCriticalSection(CRITICAL_SECTION*);

		typedef itk::Matrix
			<double,TFixedImage::ImageDimension+1,
			TFixedImage::ImageDimension+1> InitialMatrixType;

		void SetInitialTransformMatrix(InitialMatrixType InitialMatrix);
		void SetInitialTransform(Rigid3DTransformPointer pTransform);
		std::queue<CostValueInformation> GetCostValueQueue();

		void SetPreProcessorPostTransform(Rigid3DTransformPointer PostTransform);
		void SetPreProcessorPreTransform(Rigid3DTransformPointer PretTransform);

		unsigned int GetCurrentIteration();

		void SetFixedPyramid(FixedImagePyramidType*  FixedPyramid);
		void SetMovingPyramid(MovingImagePyramidType* MovingPyramid);
		void SetFixedImageRegionPyramid(  std::vector<FixedImageRegionType> FixedRegion);
		//bool IsModified();

	protected:
		MIMRegistrator()
		{
			// Images need to be set from the outside
			m_FixedImage  = NULL;
			m_MovingImage = NULL;

			// Set up internal registrator with default components
			m_Transform          = TransformType::New();
			m_Optimizer          = OptimizerType::New();
			m_Metric             = MetricType::New();
			m_Interpolator       = InterpolatorType::New();
			m_FixedImagePyramid  = FixedImagePyramidType::New();

			m_MovingImagePyramid = MovingImagePyramidType::New();
			m_Registration       = RegistrationType::New();

			m_Registration->SetTransform( m_Transform );
			m_Registration->SetOptimizer( m_Optimizer );
			m_Registration->SetMetric( m_Metric );
			m_Registration->SetInterpolator( m_Interpolator );
			
			// MultiResolutionImageRegistrationMethod

			m_Registration->SetFixedImagePyramid(m_FixedImagePyramid);
			m_Registration->SetMovingImagePyramid(m_MovingImagePyramid);

			m_Rigid3DTransform  = Rigid3DTransformType::New();

			// Setup an registration observer
			typedef SimpleMemberCommand<Self> CommandType;
			typename CommandType::Pointer command = CommandType::New();
			command->SetCallbackFunction( this, &Self::StartNewLevel );

			m_Tag = m_Registration->AddObserver( IterationEvent(), command );


			//RAMA Added
			// Setup an Optimization observer
			typename CommandType::Pointer command2 = CommandType::New();
			command2->SetCallbackFunction( this, &Self::StartNewIteration );

			m_Optimizer->AddObserver( IterationEvent(), command2 );
			//END RAMA

			// Default parameters
			m_NumberOfLevels = 1;
			m_TranslationScale = 1.0;
			m_MovingImageStandardDeviation = 0.4;
			m_FixedImageStandardDeviation = 0.4;
			m_NumberOfSpatialSamples = 50;

			m_FixedImageShrinkFactors.Fill( 1 );
			m_MovingImageShrinkFactors.Fill( 1 );

			m_NumberOfIterations = UnsignedIntArray(1);
			m_NumberOfIterations.Fill( 10 );

			m_LearningRates = DoubleArray(1);
			m_LearningRates.Fill( 1e-4 );

			m_InitialParameters = ParametersType( m_Transform->GetNumberOfParameters() );
			m_InitialParameters.Fill( 0.0 );
			m_InitialParameters[3] = 1.0;

			//RAMA
			m_stopOptimization = false;
			InitializeCriticalSection(&section);
			InitializeCriticalSection(&m_updateTransformMatrix);
			// InitializeCriticalSection(&m_ModifiedSection);

			CurrentPart = 0;
			m_ErrorStopRate = 1.02;
			NumberOfIterationsForMean = 50;
			NumberOfPartsForCompare = 4;

			m_CostArray = DoubleArray(NumberOfPartsForCompare);
			m_CostArray.Fill(0.0);
			/* m_CurrentTransform = AffineTransform<double,3>::New();*/
			m_CurrentTransform = itk::Rigid3DTransform<double>::New();
			m_CurrentTransform->SetIdentity();
			// m_Modified = false;
		}
		~MIMRegistrator();

	private:
		/** Get computed affine transform. */
		Rigid3DTransformPointer GetRigid3DTransform();

		MIMRegistrator( const Self& ); //purposely not implemented
		void operator=( const Self& ); //purposely not implemented

		typename FixedImageType::Pointer            m_FixedImage;
		typename MovingImageType::Pointer           m_MovingImage;
		typename TransformType::Pointer             m_Transform;
		typename OptimizerType::Pointer             m_Optimizer;
		typename MetricType::Pointer                m_Metric;
		typename InterpolatorType::Pointer          m_Interpolator;
		typename RecursivePyramidFilter<TFixedImage, TFixedImage>::Pointer  m_FixedImagePyramid;
		typename MovingImagePyramidType::Pointer    m_MovingImagePyramid;
		typename RegistrationType::Pointer          m_Registration;

		unsigned short                              m_NumberOfLevels;
		double                                      m_TranslationScale;
		double                                      m_MovingImageStandardDeviation;
		double                                      m_FixedImageStandardDeviation;
		unsigned short                              m_NumberOfSpatialSamples;

		UnsignedIntArray                            m_NumberOfIterations;
		DoubleArray                                 m_LearningRates;

		ShrinkFactorsArray                          m_MovingImageShrinkFactors;
		ShrinkFactorsArray                          m_FixedImageShrinkFactors;

		ParametersType                              m_InitialParameters;
		Rigid3DTransformPointer                     m_Rigid3DTransform;

		unsigned long                               m_Tag;

		//RAMA added this
		bool										  m_stopOptimization;
		CRITICAL_SECTION							  section;
		CRITICAL_SECTION							m_updateTransformMatrix;
		//CRITICAL_SECTION							m_ModifiedSection;

		Array<double>                               m_CostArray;
		unsigned int                                CurrentPart;

		double                                      m_ErrorStopRate;
		unsigned int                                NumberOfIterationsForMean;
		unsigned int                                NumberOfPartsForCompare;

		std::queue<CostValueInformation>                 CostValueQueue;

		Rigid3DTransformPointer					  m_PostTransform;
		Rigid3DTransformPointer					  m_PreTransform;

		Rigid3DTransformPointer                    m_CurrentTransform;

		//bool									  m_Modified;

	};

	template <typename TFixedImage, typename TMovingImage>
	void itk::MIMRegistrator<TFixedImage, TMovingImage>::SetFixedImageRegionPyramid( std::vector<FixedImageRegionType> FixedRegion )
	{
		m_Registration->SetFixedImageRegionPyramid(FixedRegion);
	}

	template <typename TFixedImage, typename TMovingImage>
	void itk::MIMRegistrator<TFixedImage, TMovingImage>::SetMovingPyramid( MovingImagePyramidType* MovingPyramid )
	{
		this->m_MovingImagePyramid = MovingPyramid;
		m_Registration->SetMovingImagePyramid( m_MovingImagePyramid );
	}

	template <typename TFixedImage, typename TMovingImage>
	void itk::MIMRegistrator<TFixedImage, TMovingImage>::SetFixedPyramid( FixedImagePyramidType* FixedPyramid )
	{
		this->m_FixedImagePyramid = FixedPyramid;
		m_Registration->SetFixedImagePyramid( m_FixedImagePyramid );
		if (m_FixedImagePyramid->GetImage())
		{
			m_Registration->SetFixedImageRegion(m_FixedImagePyramid->GetImage()->GetBufferedRegion());
		}
		 m_Registration->SetInitialTransformParameters( m_InitialParameters );
		m_Registration->SetPyramidFlag();
	}

} // namespace itk

#ifndef ITK_MANUAL_INSTANTIATION
#include "MIMRegistrator.txx"
#endif

#endif
