#pragma once
#include "RecursivePyramidFilter.h"
#include "ClaculateShrinkFactor.h"

 

	template <typename TImage>
	class  misPyramidCalculator : public itk::ProcessObject
	{
public:
	  typedef misPyramidCalculator  Self;
	  typedef ProcessObject  Superclass;
	  typedef itk::SmartPointer<Self>   Pointer;
	  typedef itk::SmartPointer<const Self>  ConstPointer;

	  itkNewMacro(Self);

	  typedef          TImage                     InputImageType;
	  typedef typename InputImageType::ConstPointer    InputImageConstPointer;
	  typedef typename InputImageType::RegionType      ImageRegionType;

	  typedef  itk::RecursivePyramidFilter<InputImageType, InputImageType> ImagePyramidType;
	  typedef typename ImagePyramidType::Pointer  ImagePyramidPointer;

	  typedef itk::Array2D<unsigned int>          ScheduleType;

	  itkSetConstObjectMacro( InputImage, InputImageType );
	  itkGetConstObjectMacro( InputImage, InputImageType );
	  itkSetMacro( ImageRegion, ImageRegionType );
	  itkGetConstReferenceMacro( ImageRegion, ImageRegionType );
	  itkSetObjectMacro( ImagePyramid, ImagePyramidType );
	  itkGetObjectMacro( ImagePyramid, ImagePyramidType );
	  itkGetConstMacro( ImagePyramidSchedule, ScheduleType );
	  itkGetMacro( NumberOfLevels, unsigned long );
	  itkGetMacro( CurrentLevel, unsigned long );

	  void SetNumberOfLevels( unsigned long numberOfLevels ){
		  if( m_PyramidCalculatorScheduleSpecified )
		  {
			  itkExceptionMacro( "SetNumberOfLevels should not be used "
				  << "if schedules have been specified using SetSchedules method " );
		  }

		  m_NumberOfLevels = numberOfLevels;
		  m_NumberOfLevelsSpecified = true;
		  this->Modified();
	  }
	  bool PreparePyramid(void)
	  {
		  bool res = false;
		  if( !m_InputImage )
			  {
			  	itkExceptionMacro(<<"FixedImage is not present");
			  }

			  if( !m_ImagePyramid )
			  {
			  	itkExceptionMacro(<<"Fixed image pyramid is not present");
			  }

			  // Setup the fixed image pyramid
			  if( m_NumberOfLevelsSpecified )
			  {
			  	m_ImagePyramid->SetNumberOfLevels( m_NumberOfLevels );
			  }

// 			  if( m_PyramidCalculatorScheduleSpecified )
// 			  {
// 			  	m_ImagePyramid->SetNumberOfLevels( m_ImagePyramidSchedule.rows());
// 			  	m_ImagePyramid->SetSchedule( m_ImagePyramidSchedule );
//
// 			  }
			  double start(clock());
			  double finish(clock());

			  m_ImagePyramid->SetInput( m_InputImage );

			  start = clock();

			  m_ImagePyramid->UpdateLargestPossibleRegion();

			  finish = clock();
			  double duration=(finish-start) / CLOCKS_PER_SEC;
			  duration = duration * 1000;

			  typedef typename ImageRegionType::SizeType         SizeType;
			  typedef typename ImageRegionType::IndexType        IndexType;

			  ScheduleType schedule = m_ImagePyramid->GetSchedule();
			  if (schedule.empty())
			  {
				  cout<<"+++++++++++++++++++Schedule is empty"<<endl;
				  _ASSERT( 0 == 1);
				  return res;
			  }
			  SizeType  inputSize  = m_ImageRegion.GetSize();
			  IndexType inputStart = m_ImageRegion.GetIndex();

			  const unsigned long numberOfLevels =
			  	m_ImagePyramid->GetNumberOfLevels();

			  m_ImageRegionPyramid.reserve( numberOfLevels );
			  m_ImageRegionPyramid.resize( numberOfLevels );

			  // Compute the FixedImageRegion corresponding to each level of the
			  // pyramid. This uses the same algorithm of the ShrinkImageFilter
			  // since the regions should be compatible.
			  for ( unsigned int level=0; level < numberOfLevels; level++ )
			  {
			  	SizeType  size;
			  	IndexType start;
			  	for ( unsigned int dim = 0; dim < TImage::ImageDimension; dim++)
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
			  	m_ImageRegionPyramid[ level ].SetSize( size );
			  	m_ImageRegionPyramid[ level ].SetIndex( start );
			  }
			  ClaculateShrinkFactor ShrinkFactorArrayCalc;
			  this->m_ImagePyramid->SetStartingShrinkFactors(ShrinkFactorArrayCalc.GetShrinkFactor(m_Spacing , m_NumberOfLevels).GetDataPointer());
			  res = true;
			  return res;
	  }
	  std::vector<ImageRegionType> GetImageRegionPyramid()
	  {
		  return m_ImageRegionPyramid;
	  }

	  void SetImageSpacing(double* spacing)
	  {
		  for (int i = 0 ; i< TImage::ImageDimension; i++)
		  {
			  this->m_Spacing[i] = spacing[i];
		  }
	  }

protected:
	  misPyramidCalculator(){
		  this->SetNumberOfRequiredOutputs( 1 );  // for the Transform

		  m_InputImage   = 0; // has to be provided by the user.

		  m_ImagePyramid  = ImagePyramidType::New();
		  m_NumberOfLevels = 1;
		  m_CurrentLevel = 0;

		  m_Stop = false;

		  m_PyramidCalculatorScheduleSpecified = false;
		  m_NumberOfLevelsSpecified = false;
		  m_Spacing.resize(TImage::ImageDimension);
	  }
	  virtual ~misPyramidCalculator() {};
	  itkSetMacro( CurrentLevel, unsigned long );

private:
	  InputImageConstPointer           m_InputImage;
	  ImagePyramidPointer              m_ImagePyramid;
	  ImageRegionType				   m_ImageRegion;
	  std::vector<ImageRegionType>     m_ImageRegionPyramid;
	  unsigned long                    m_NumberOfLevels;
	  unsigned long                    m_CurrentLevel;
	  bool                             m_Stop;
	  ScheduleType                     m_ImagePyramidSchedule;
	  bool                             m_PyramidCalculatorScheduleSpecified;
	  bool                             m_NumberOfLevelsSpecified;
	  std::vector<double>			   m_Spacing;
	};
