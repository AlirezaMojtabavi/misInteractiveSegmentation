#pragma once

#pragma warning (push)
#pragma warning (disable : 4290)
 
#include "misPyramidCalculator.h"
#include "RecursivePyramidFilter.h"

namespace itk
{
/** \class MultiResolutionImageRegistrationMethod
 * \brief Base class for multi-resolution image registration methods
 *
 * This class provides a generic interface for multi-resolution
 * registration using components of the registration framework.
 * See documentation for ImageRegistrationMethod for a description
 * of the registration framework components.
 *
 * The registration process is initiated by method StartRegistration().
 * The user must set the parameters of each component before calling
 * this method.
 *
 * The number of resolution level to process can be set via
 * SetNumberOfLevels(). At each resolution level, the user specified
 * registration components are used to register downsampled version of the
 * images by computing the transform parameters that will map one image onto
 * the other image.
 *
 * A user can specify schedules for the fixed and moving image using
 * SetSchedules() method.  However, SetNumberOfLevels() and SetSchedules()
 * should not be used together. An exception will be thrown if that happens.
 *
 * The downsampled images are provided by user specified
 * MultiResolutionPyramidImageFilters. User must specify the schedule
 * for each pyramid externally prior to calling StartRegistration().
 *
 * \warning If there is discrepancy between the number of level requested
 * and a pyramid schedule. The pyramid schedule will be overriden
 * with a default one.
 *
 * Before each resolution level an IterationEvent is invoked providing an
 * opportunity for a user interface to change any of the components,
 * change component parameters, or stop the registration.
 *
 * This class is templated over the fixed image type and the moving image
 * type.
 *
 * \sa ImageRegistrationMethod
 * \ingroup RegistrationFilters
 */
template <typename TFixedImage, typename TMovingImage>
class misMultiResolutionImageRegistrationMethod : public ProcessObject
{
public:
  /** Standard class typedefs. */
  typedef misMultiResolutionImageRegistrationMethod  Self;
  typedef ProcessObject  Superclass;
  typedef SmartPointer<Self>   Pointer;
  typedef SmartPointer<const Self>  ConstPointer;

  /** Method for creation through the object factory. */
  itkNewMacro(Self);

  /** Run-time type information (and related methods). */
  itkTypeMacro(misMultiResolutionImageRegistrationMethod, ProcessObject);

  /**  Type of the Fixed image. */
  typedef          TFixedImage                     FixedImageType;
  typedef typename FixedImageType::ConstPointer    FixedImageConstPointer;
  typedef typename FixedImageType::RegionType      FixedImageRegionType;

  /**  Type of the Moving image. */
  typedef          TMovingImage                    MovingImageType;
  typedef typename MovingImageType::ConstPointer   MovingImageConstPointer;

  /**  Type of the metric. */
  typedef ImageToImageMetric< FixedImageType,
							  MovingImageType >    MetricType;
  typedef typename MetricType::Pointer             MetricPointer;

  /**  Type of the Transform . */
  typedef typename MetricType::TransformType       TransformType;
  typedef typename TransformType::Pointer          TransformPointer;

  /** Type for the output: Using Decorator pattern for enabling
   *  the Transform to be passed in the data pipeline */
  typedef  DataObjectDecorator< TransformType >    TransformOutputType;
  typedef typename TransformOutputType::Pointer    TransformOutputPointer;
  typedef typename TransformOutputType::ConstPointer    TransformOutputConstPointer;

  /**  Type of the Interpolator. */
  typedef typename MetricType::InterpolatorType    InterpolatorType;
  typedef typename InterpolatorType::Pointer       InterpolatorPointer;

  /**  Type of the optimizer. */
  typedef SingleValuedNonLinearOptimizer           OptimizerType;

  /** Type of the Fixed image multiresolution pyramid. */

  //RAMA Comment This
  /*typedef MultiResolutionPyramidImageFilter< FixedImageType,
											 FixedImageType >
  FixedImagePyramidType;*/

  typedef RecursivePyramidFilter<FixedImageType, FixedImageType> FixedImagePyramidType;
  typedef typename FixedImagePyramidType::Pointer  FixedImagePyramidPointer;

  /** Type of pyramid schedule type */

  //RAMA Comment This
  //typedef typename FixedImagePyramidType::ScheduleType              ScheduleType;
  typedef Array2D<unsigned int>          ScheduleType;

  /** Type of the moving image multiresolution pyramid. */
 /* typedef MultiResolutionPyramidImageFilter< MovingImageType,
											 MovingImageType >
  MovingImagePyramidType;*/
  typedef RecursivePyramidFilter<MovingImageType, MovingImageType> MovingImagePyramidType;
  typedef typename MovingImagePyramidType::Pointer MovingImagePyramidPointer;

  /** Type of the Transformation parameters This is the same type used to
   *  represent the search space of the optimization algorithm */
  typedef  typename MetricType::TransformParametersType    ParametersType;

  /** Smart Pointer type to a DataObject. */
  typedef typename DataObject::Pointer DataObjectPointer;

  typedef misPyramidCalculator< FixedImageType >    PyramidCalculator;
  typedef typename PyramidCalculator::Pointer          PyramidCalculatorPointer;

  /** Method that initiates the registration. */
  void StartRegistration()
  {
	    // StartRegistration is an old API from before
  // this egistrationMethod was a subclass of ProcessObject.
  // Historically, one could call StartRegistration() instead of
  // calling Update().  However, when called directly by the user, the
  // inputs to the RegistrationMethod may not be up to date.  This
  // may cause an unexpected behavior.
  //
  // Since we cannot eliminate StartRegistration for backward
  // compability reasons, we check whether StartRegistration was
  // called directly or whether Update() (which in turn called 
  // StartRegistration()).


  //RAMA added this
  double start(clock());
  double finish(clock());
  //RAMA

  if(m_Stop)
	  return;

   if (!m_Updating)
    {
    this->Update();
    }
  else
    {
		m_Stop = false;

		if(m_IsPyramidPreparedExternally == false)
		{
			start = clock();
    		this->PreparePyramids();

		
		
			finish = clock();
			double duration=(finish-start) / CLOCKS_PER_SEC;
			duration = duration * 1000;
	
			start = clock();
			
		}
		

		for ( m_CurrentLevel = 0; m_CurrentLevel < m_NumberOfLevels;
         m_CurrentLevel++ )
		{
      
			// Invoke an iteration event.
			// This allows a UI to reset any of the components between
			// resolution level.
			this->InvokeEvent( IterationEvent() );
      
			// Check if there has been a stop request
			if ( m_Stop ) 
			{
				break;
			}
      
			try
			{
			// initialize the interconnects between components
				this->Initialize();
			}
			catch( ExceptionObject& err )
			{
				m_LastTransformParameters = ParametersType(1);
				m_LastTransformParameters.Fill( 0.0f );
        
				// pass exception to caller
				throw err;
			}
      
			try
			{
				m_Optimizer->StartOptimization();
			}

			catch( ExceptionObject& err )
			{
				// An error has occurred in the optimization.
				// Update the parameters
				m_LastTransformParameters = m_Optimizer->GetCurrentPosition();
        
				// Pass exception to caller
				throw err;
			}
      
			// get the results
			m_LastTransformParameters = m_Optimizer->GetCurrentPosition();
			m_Transform->SetParameters( m_LastTransformParameters );
      
			// setup the initial parameters for next level
			if ( m_CurrentLevel < m_NumberOfLevels - 1 )
			{
			m_InitialTransformParametersOfNextLevel =
				m_LastTransformParameters;
			}
	 
      }//End for

		finish = clock();
		double durations=(finish-start) / CLOCKS_PER_SEC;
		durations = durations * 1000;
	}//End else
  
  }

  /** Method to stop the registration. */
  void StopRegistration()
  {
	  m_Stop = true;
  }
 

  /** Set/Get the Fixed image. */
  itkSetConstObjectMacro( FixedImage, FixedImageType );
  itkGetConstObjectMacro( FixedImage, FixedImageType );

  /** Set/Get the Moving image. */
  itkSetConstObjectMacro( MovingImage, MovingImageType );
  itkGetConstObjectMacro( MovingImage, MovingImageType );

  /** Set/Get the Optimizer. */
  itkSetObjectMacro( Optimizer,  OptimizerType );
  itkGetObjectMacro( Optimizer,  OptimizerType );

  /** Set/Get the Metric. */
  itkSetObjectMacro( Metric, MetricType );
  itkGetObjectMacro( Metric, MetricType );

  /** Set/Get the Metric. */
  itkSetMacro( FixedImageRegion, FixedImageRegionType );
  itkGetConstReferenceMacro( FixedImageRegion, FixedImageRegionType );

  /** Set/Get the Transfrom. */
  itkSetObjectMacro( Transform, TransformType );
  itkGetObjectMacro( Transform, TransformType );

  /** Set/Get the Interpolator. */
  itkSetObjectMacro( Interpolator, InterpolatorType );
  itkGetObjectMacro( Interpolator, InterpolatorType );

  /** Set/Get the Fixed image pyramid. */
  itkSetObjectMacro( FixedImagePyramid, FixedImagePyramidType );
  itkGetObjectMacro( FixedImagePyramid, FixedImagePyramidType );

  /** Set/Get the Moving image pyramid. */
  itkSetObjectMacro( MovingImagePyramid, MovingImagePyramidType );
  itkGetObjectMacro( MovingImagePyramid, MovingImagePyramidType );

  /** Set/Get the schedules . */
  void SetSchedules( const ScheduleType & fixedSchedule,
					const ScheduleType & movingSchedule )
  {
	  if( m_NumberOfLevelsSpecified )
	  {
		  itkExceptionMacro( "SetSchedules should not be used " 
			  << "if numberOfLevelves are specified using SetNumberOfLevels" );
	  }
	  m_FixedImagePyramidSchedule = fixedImagePyramidSchedule;
	  m_MovingImagePyramidSchedule = movingImagePyramidSchedule;
	  m_ScheduleSpecified = true;

	  //Set the number of levels based on the pyramid schedule specified
	  if ( m_FixedImagePyramidSchedule.rows() != 
		  m_MovingImagePyramidSchedule.rows())
	  {
		  itkExceptionMacro("The specified schedules contain unequal number of levels");
	  }
	  else
	  {
		  m_NumberOfLevels = m_FixedImagePyramidSchedule.rows();
	  }

	  this->Modified();
  }
  itkGetConstMacro( FixedImagePyramidSchedule, ScheduleType );
  itkGetConstMacro( MovingImagePyramidSchedule, ScheduleType );

  /** Set/Get the number of multi-resolution levels. */
  void SetNumberOfLevels( unsigned long numberOfLevels )
  {
	  if( m_ScheduleSpecified )
	  {
		  itkExceptionMacro( "SetNumberOfLevels should not be used " 
			  << "if schedules have been specified using SetSchedules method " );
	  }

	  m_NumberOfLevels = numberOfLevels;
	  m_NumberOfLevelsSpecified = true;
	  this->Modified();
  }
  itkGetMacro( NumberOfLevels, unsigned long );

  /** Get the current resolution level being processed. */
  itkGetMacro( CurrentLevel, unsigned long );

  /** Set/Get the initial transformation parameters. */
  itkSetMacro( InitialTransformParameters, ParametersType );
  itkGetConstReferenceMacro( InitialTransformParameters, ParametersType );

  /** Set/Get the initial transformation parameters of the next resolution
   level to be processed. The default is the last set of parameters of
   the last resolution level. */
  itkSetMacro( InitialTransformParametersOfNextLevel, ParametersType );
  itkGetConstReferenceMacro( InitialTransformParametersOfNextLevel, ParametersType );

  /** Get the last transformation parameters visited by
   * the optimizer. */
  itkGetConstReferenceMacro( LastTransformParameters, ParametersType );

  /** Returns the transform resulting from the registration process  */
  const TransformOutputType * GetOutput() const
  {
	  return static_cast< const TransformOutputType * >( this->ProcessObject::GetOutput(0) );
  }

  /** Make a DataObject of the correct type to be used as the specified
   * output. */
  virtual DataObjectPointer MakeOutput(unsigned int output)
  {
	  switch (output)
	  {
	  case 0:
		  return static_cast<DataObject*>(TransformOutputType::New().GetPointer());
		  break;
	  default:
		  itkExceptionMacro("MakeOutput request for an output number larger than the expected number of outputs");
		  return 0;
	  }
  }

  /** Method to return the latest modified time of this object or
   * any of its cached ivars */
  unsigned long GetMTime() const
  {
	  unsigned long mtime = Superclass::GetMTime();
	  unsigned long m;


	  // Some of the following should be removed once ivars are put in the
	  // input and output lists

	  if (m_Transform)
	  {
		  m = m_Transform->GetMTime();
		  mtime = (m > mtime ? m : mtime);
	  }

	  if (m_Interpolator)
	  {
		  m = m_Interpolator->GetMTime();
		  mtime = (m > mtime ? m : mtime);
	  }

	  if (m_Metric)
	  {
		  m = m_Metric->GetMTime();
		  mtime = (m > mtime ? m : mtime);
	  }

	  if (m_Optimizer)
	  {
		  m = m_Optimizer->GetMTime();
		  mtime = (m > mtime ? m : mtime);
	  }

	  if (m_FixedImage)
	  {
		  m = m_FixedImage->GetMTime();
		  mtime = (m > mtime ? m : mtime);
	  }

	  if (m_MovingImage)
	  {
		  m = m_MovingImage->GetMTime();
		  mtime = (m > mtime ? m : mtime);
	  }

	  return mtime;

  }
  void Reset()
  {
	  this->SetNumberOfRequiredOutputs( 1 );  // for the Transform

	  m_FixedImage   = 0; 
	  m_MovingImage  = 0; 
	  m_Transform    = 0; 
	  m_Interpolator = 0; 
	  m_Metric       = 0; 
	  m_Optimizer    = 0; 
 	  m_FixedImagePyramid  = FixedImagePyramidType::New(); 
	  m_MovingImagePyramid = MovingImagePyramidType::New();
	  m_NumberOfLevels = 1;
	  m_CurrentLevel = 0;

	  m_Stop = false;

	  m_ScheduleSpecified = false;
	  m_NumberOfLevelsSpecified = false;

	  m_InitialTransformParameters = ParametersType(1);
	  m_InitialTransformParametersOfNextLevel = ParametersType(1);
	  m_LastTransformParameters = ParametersType(1);

	  m_InitialTransformParameters.Fill( 0.0f );
	  m_InitialTransformParametersOfNextLevel.Fill( 0.0f );
	  m_LastTransformParameters.Fill( 0.0f );
	  m_IsPyramidPreparedExternally = false;

	  TransformOutputPointer transformDecorator = 
		  static_cast< TransformOutputType * >( 
			  this->MakeOutput(0).GetPointer() );

	  this->ProcessObject::SetNthOutput( 0, transformDecorator.GetPointer() );
  }

	void SetPyramidFlag();
	void SetTransformExternally();
	void SetFixedImageRegionPyramid(  std::vector<FixedImageRegionType> fixedRegion);
protected:

  misMultiResolutionImageRegistrationMethod()
  {
	  Reset();
  }

  virtual ~misMultiResolutionImageRegistrationMethod() {};
 
  /** Method invoked by the pipeline in order to trigger the computation of
   * the registration. */
  void  GenerateData ()
  {
	  if(m_Stop == false)
		  this->StartRegistration();
  }

  /** Initialize by setting the interconnects between the components.
	  This method is executed at every level of the pyramid with the
	  values corresponding to this resolution
   */
  void Initialize() throw (ExceptionObject)
  {
	  // Sanity checks
  if ( !m_Metric )
    {
    itkExceptionMacro(<<"Metric is not present" );
    }

  if ( !m_Optimizer )
    {
    itkExceptionMacro(<<"Optimizer is not present" );
    }

  if( !m_Transform )
    {
    itkExceptionMacro(<<"Transform is not present");
    }

  if( !m_Interpolator )
    {
    itkExceptionMacro(<<"Interpolator is not present");
    }
  m_Metric->SetMovingImage( m_MovingImagePyramid->GetOutput(m_CurrentLevel) );
  m_Metric->SetFixedImage( m_FixedImagePyramid->GetOutput(m_CurrentLevel) );
  m_Metric->SetTransform( m_Transform );
  m_Metric->SetInterpolator( m_Interpolator );
  m_Metric->SetFixedImageRegion( m_FixedImageRegionPyramid[ m_CurrentLevel ] );
  m_Metric->Initialize();

  // Setup the optimizer
  m_Optimizer->SetCostFunction( m_Metric );
 

  if(this->m_IsTransformAppliedExternally == false)
  {
	 m_Optimizer->SetInitialPosition( m_InitialTransformParametersOfNextLevel );
  }
  else if(this->m_IsTransformAppliedExternally == true)
  {
	 this->m_IsTransformAppliedExternally = false;
  }
   TransformOutputType * transformOutput =  
     static_cast< TransformOutputType * >( this->ProcessObject::GetOutput(0) );

  transformOutput->Set( m_Transform.GetPointer() );

 

  }

  /** Compute the size of the fixed region for each level of the pyramid. */
  void PreparePyramids( void )
  {
	  if( !m_Transform )
	  {
		  itkExceptionMacro(<<"Transform is not present");
	  }

	  m_InitialTransformParametersOfNextLevel = m_InitialTransformParameters;

	  if ( m_InitialTransformParametersOfNextLevel.Size() != 
		  m_Transform->GetNumberOfParameters() )
	  {
		  itkExceptionMacro(<<"Size mismatch between initial parameter and transform"); 
	  }

	  // Sanity checks
	  if( !m_FixedImage )
	  {
		  itkExceptionMacro(<<"FixedImage is not present");
	  }

	  if( !m_MovingImage )
	  {
		  itkExceptionMacro(<<"MovingImage is not present");
	  }

	  if( !m_FixedImagePyramid )
	  {
		  itkExceptionMacro(<<"Fixed image pyramid is not present");
	  }

	  if( !m_MovingImagePyramid )
	  {
		  itkExceptionMacro(<<"Moving image pyramid is not present");
	  }

	  // Setup the fixed and moving image pyramid
	  if( m_NumberOfLevelsSpecified )
	  {
		  m_FixedImagePyramid->SetNumberOfLevels( m_NumberOfLevels );
		  m_MovingImagePyramid->SetNumberOfLevels( m_NumberOfLevels );
	  }

	  if( m_ScheduleSpecified )
	  {
		  m_FixedImagePyramid->SetNumberOfLevels( m_FixedImagePyramidSchedule.rows());
		  m_FixedImagePyramid->SetSchedule( m_FixedImagePyramidSchedule );

		  m_MovingImagePyramid->SetNumberOfLevels( m_MovingImagePyramidSchedule.rows());
		  m_MovingImagePyramid->SetSchedule( m_MovingImagePyramidSchedule );
	  }

	  double start(clock());
	  double finish(clock());

	  m_FixedImagePyramid->SetInput( m_FixedImage );
	  start = clock();
	  m_FixedImagePyramid->UpdateLargestPossibleRegion();
	  finish = clock();
	  double duration=(finish-start) / CLOCKS_PER_SEC;
	  duration = duration * 1000;

	  // Setup the moving image pyramid
	  m_MovingImagePyramid->SetInput( m_MovingImage );
	  start = clock();
	  m_MovingImagePyramid->UpdateLargestPossibleRegion();
	  finish = clock();
	  duration=(finish-start) / CLOCKS_PER_SEC;
	  duration = duration * 1000;

	  typedef typename FixedImageRegionType::SizeType         SizeType;
	  typedef typename FixedImageRegionType::IndexType        IndexType;

	  ScheduleType schedule = m_FixedImagePyramid->GetSchedule();

	  ScheduleType movingschedule = m_MovingImagePyramid->GetSchedule();

	  SizeType  inputSize  = m_FixedImageRegion.GetSize();
	  IndexType inputStart = m_FixedImageRegion.GetIndex();

	  const unsigned long numberOfLevels = 
		  m_FixedImagePyramid->GetNumberOfLevels(); 

	  m_FixedImageRegionPyramid.reserve( numberOfLevels );
	  m_FixedImageRegionPyramid.resize( numberOfLevels );

	  // Compute the FixedImageRegion corresponding to each level of the 
	  // pyramid. This uses the same algorithm of the ShrinkImageFilter 
	  // since the regions should be compatible. 
	  for ( unsigned int level=0; level < numberOfLevels; level++ )
	  {
		  SizeType  size;
		  IndexType start;
		  for ( unsigned int dim = 0; dim < TFixedImage::ImageDimension; dim++)
		  {
			  const float scaleFactor = static_cast<float>( schedule[ level ][ dim ] );

			  size[ dim ] = static_cast<typename SizeType::SizeValueType>(
				  vcl_floor(static_cast<float>( inputSize[ dim ] ) / scaleFactor ) );
			  if( size[ dim ] < 1 )
			  {
				  size[ dim ] = 1;
			  }

			  start[ dim ] = static_cast<typename IndexType::IndexValueType>(
				  vcl_ceil(static_cast<float>( inputStart[ dim ] ) / scaleFactor ) ); 
		  }
		  m_FixedImageRegionPyramid[ level ].SetSize( size );
		  m_FixedImageRegionPyramid[ level ].SetIndex( start );
	  }

  }

  /** Set the current level to be processed */
  itkSetMacro( CurrentLevel, unsigned long );

private:
  misMultiResolutionImageRegistrationMethod(const Self&); //purposely not implemented
  void operator=(const Self&); //purposely not implemented

  MetricPointer             m_Metric;
  OptimizerType::Pointer    m_Optimizer;
  MovingImageConstPointer   m_MovingImage = 0;
  FixedImageConstPointer    m_FixedImage = 0;
  TransformPointer          m_Transform;
  InterpolatorPointer       m_Interpolator;
  MovingImagePyramidPointer m_MovingImagePyramid;
  FixedImagePyramidPointer  m_FixedImagePyramid;
  ParametersType m_InitialTransformParameters;
  ParametersType m_InitialTransformParametersOfNextLevel;
  ParametersType m_LastTransformParameters;
  FixedImageRegionType m_FixedImageRegion;
  std::vector<FixedImageRegionType>  m_FixedImageRegionPyramid;
  unsigned long m_NumberOfLevels;
  unsigned long m_CurrentLevel;
  bool m_Stop;
  ScheduleType m_FixedImagePyramidSchedule;
  ScheduleType m_MovingImagePyramidSchedule;
  bool m_ScheduleSpecified;
  bool m_NumberOfLevelsSpecified;
  bool m_IsPyramidPreparedExternally;
  bool m_IsTransformAppliedExternally;
};

template <typename TFixedImage, typename TMovingImage>
void itk::misMultiResolutionImageRegistrationMethod<TFixedImage, TMovingImage>::SetFixedImageRegionPyramid( std::vector<FixedImageRegionType> fixedRegion )
{
	this->m_FixedImageRegionPyramid = fixedRegion;
}

template <typename TFixedImage, typename TMovingImage>
void itk::misMultiResolutionImageRegistrationMethod<TFixedImage, TMovingImage>::SetPyramidFlag()
{
	m_IsPyramidPreparedExternally = true;
	 m_InitialTransformParametersOfNextLevel = m_InitialTransformParameters;
}

	template <typename TFixedImage, typename TMovingImage>
void itk::misMultiResolutionImageRegistrationMethod<TFixedImage, TMovingImage>::SetTransformExternally()
{
	m_IsTransformAppliedExternally = true;
}
} // end namespace itk

#pragma warning (pop)