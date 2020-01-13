#ifndef _MultiResolutionRegistration_h
#define _MultiResolutionRegistration_h

#include "MIMApplicationBase.h"
#include "MIMPreprocessor.h"
#include "MIMRegistrator.h"
#include "SimpleAppOutput.h"
#include "RecursivePyramidFilter.h"

template < class TInputPixel, 
class TInputImage = itk::Image<TInputPixel, 3>,
class TImage = itk::Image<float,3> >

class MultiResolutionRegistration : public itk::MIMApplicationBase <TInputImage, TImage,	
	itk::MIMPreprocessor<TInputImage,TImage>, itk::MIMRegistrator<TImage,TImage>, itk::SimpleAppOutput<TInputImage>>   
{
public:
	/** Standard class typedefs. */
	typedef itk::RecursivePyramidFilter<itk::Image<float,3>,itk::Image<float,3>> ImagePyramidType;
	typedef itk::Image<float,3>::RegionType FixedImageRegionType;
	typedef MultiResolutionRegistration Self;
	typedef itk::MIMApplicationBase < 
		TInputImage, TImage,
		itk::MIMPreprocessor<TInputImage,TImage>,
		itk::MIMRegistrator<TImage,TImage>,
		itk::SimpleAppOutput<TInputImage> >       Superclass;
	typedef itk::SmartPointer<Self> Pointer;
	typedef itk::SmartPointer<const Self>  ConstPointer;

	/** Run-time type information (and related methods). */
	itkTypeMacro(MultiResolutionRegistration, MIMApplicationBase);

	/** Method for creation through the object factory. */
	itkNewMacro(Self);

	////////////////Inline functions/////////////

	static unsigned __stdcall ThreadStaticEntryPoint(void * pThis)
	{

		
		MIMApplicationBase *pthX = (MIMApplicationBase*)pThis;
		pthX->Execute();  
		_endthreadex( 0 );

		return 1;        
	}

	//Converting a 4*4 Matrix to a PermuteOrder array
	//The i-th axis of the output image corresponds with the order[i]-th axis of the input image.
	itk::FixedArray<unsigned int, TInputImage::ImageDimension> 
		ConvertPermuteOrder(itk::Matrix<int,TInputImage::ImageDimension,
		TInputImage::ImageDimension> inputMatrix);

	itk::FixedArray<bool, TInputImage::ImageDimension> ConvertFlipOrder
		(itk::Matrix<int,TInputImage::ImageDimension,TInputImage::ImageDimension> 
		inputMatrix);

	HANDLE CallExecute_SeprateThread();
	void SetFixedPyramid(ImagePyramidType* FixedPyramid);
	void SetMovingPyramid(ImagePyramidType* MovingPyramid);
	void SetFixedImageRegionPyramid(  std::vector<FixedImageRegionType> fixedRegion);
	///////////////////////////////////////////

protected:
	MultiResolutionRegistration()
	{};

	virtual ~MultiResolutionRegistration(){};

	
	/*** Initialize the output generator. */
	virtual void InitializeGenerator()
	{
		this->m_Generator->SetFixedImage( MIMApplicationBase::m_FixedImage );
		this->m_Generator->SetMovingImage(MIMApplicationBase::m_MovingImage );
		this->m_Generator->SetTransform( this->m_Transform );
		this->m_Generator->SetOutputFileName( this->GetOutputFileName() );
	};
};

#ifndef ITK_MANUAL_INSTANTIATION
#include "MultiResolutionRegistration.txx"
#endif

#endif
