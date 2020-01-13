#ifndef _RecursivePyramidFilter_txx
#define _RecursivePyramidFilter_txx

#pragma warning (push, 0)

#include "RecursivePyramidFilter.h"
#include "itkShrinkImageFilter.h"
#include "itkGaussianOperator.h"
#include "itkCastImageFilter.h"
#include "itkDiscreteGaussianImageFilter.h"
#include "itkExceptionObject.h"
#include <ctime>

#include "vnl/vnl_math.h"
#include "itkArray.h"

using namespace std;

namespace itk
{


/*
* Constructor
*/
template <class TInputImage, class TOutputImage>
RecursivePyramidFilter<TInputImage, TOutputImage>
	::RecursivePyramidFilter()
{
	m_NumberOfLevels = 0;
}


/*
* GenerateData
*/
template <class TInputImage, class TOutputImage>
void
	RecursivePyramidFilter<TInputImage, TOutputImage>
	::GenerateData()
{
   if(m_Schedule.empty())
 	  return;
  int ilevel;
  unsigned int idim;
  bool         allOnes;
  typename TOutputImage::RegionType  LPRegion;

  double start(clock());
  double finish(clock());

  //Kernel[0][0][0] = 0;
  //Kernel[0][0][1] = 0;
  //Kernel[0][0][2] = 0;

  //Kernel[0][1][0] = 0;
  //Kernel[0][1][1] = 1;
  //Kernel[0][1][2] = 0;

  //Kernel[0][2][0] = 0;
  //Kernel[0][2][1] = 0;
  //Kernel[0][2][2] = 0;

  //Kernel[1][0][0] = 0;
  //Kernel[1][0][1] = 1;
  //Kernel[1][0][2] = 0;

  //Kernel[1][1][0] = 1;
  //Kernel[1][1][1] = 1;
  //Kernel[1][1][2] = 1;

  //Kernel[1][2][0] = 0;
  //Kernel[1][2][1] = 1;
  //Kernel[1][2][2] = 0;

  //Kernel[2][0][0] = 0;
  //Kernel[2][0][1] = 0;
  //Kernel[2][0][2] = 0;

  //Kernel[2][1][0] = 0;
  //Kernel[2][1][1] = 1;
  //Kernel[2][1][2] = 0;

  //Kernel[2][2][0] = 0;
  //Kernel[2][2][1] = 0;
  //Kernel[2][2][2] = 0;

  Kernel[0][0][0] = 1;
  Kernel[0][0][1] = 1;
  Kernel[0][0][2] = 1;

  Kernel[0][1][0] = 1;
  Kernel[0][1][1] = 1;
  Kernel[0][1][2] = 1;

  Kernel[0][2][0] = 1;
  Kernel[0][2][1] = 1;
  Kernel[0][2][2] = 1;

  Kernel[1][0][0] = 1;
  Kernel[1][0][1] = 1;
  Kernel[1][0][2] = 1;

  Kernel[1][1][0] = 1;
  Kernel[1][1][1] = 1;
  Kernel[1][1][2] = 1;

  Kernel[1][2][0] = 1;
  Kernel[1][2][1] = 1;
  Kernel[1][2][2] = 1;

  Kernel[2][0][0] = 1;
  Kernel[2][0][1] = 1;
  Kernel[2][0][2] = 1;

  Kernel[2][1][0] = 1;
  Kernel[2][1][1] = 1;
  Kernel[2][1][2] = 1;

  Kernel[2][2][0] = 1;
  Kernel[2][2][1] = 1;
  Kernel[2][2][2] = 1;

  typedef CastImageFilter<TInputImage, TOutputImage> CasterType; 
  typename CasterType::Pointer   caster   = CasterType::New();

  // recursively compute outputs starting from the last one
  for( ilevel = this->GetNumberOfLevels() - 1; ilevel > -1; ilevel--)
	{
		
		this->UpdateProgress( 1.0 - static_cast<float>( 1 + ilevel ) /
                      static_cast<float>( this->GetNumberOfLevels() ) );

		// Check shrink factors and compute variances
		allOnes = true;
		for( idim = 0; idim < ImageDimension; idim++ )
		{
		 if( ilevel == static_cast<int>(this->GetNumberOfLevels()) - 1)
		 {			 
			factors[idim] = m_Schedule[ilevel][idim]/*this->GetSchedule()[ilevel][idim]*/;
		 }
		 else
		 {
			factors[idim] = this->GetSchedule()[ilevel][idim] /
			  this->GetSchedule()[ilevel+1][idim];
		 }
		 if( factors[idim] != 1 ) 
		 { 
		    allOnes = false; 
		 }
	     
	   }//End For idim

	   if( (allOnes) && (ilevel != static_cast<int>(this->GetNumberOfLevels()) - 1 ))
       {
             OutputList[ilevel] = OutputList[ilevel + 1];
       }
       else
       {
		     //Allocate Memory for Output Image
			 typedef itk::Image<float,3> ImageType;
			 ImageType::Pointer imagePtr = ImageType::New();
	   
			 ImageType::SizeType outputImageSize;
			 
			 if (ilevel == static_cast<int>(this->GetNumberOfLevels()) - 1)
			 {
				InputImageSize = m_InputImage->
			    GetLargestPossibleRegion().GetSize();
			 }
			 else
			 {
			 InputImageSize = OutputList[ilevel + 1]->
				 GetLargestPossibleRegion().GetSize();
			 }

			 for (int i=0;i<3;i++)
			 {
				 outputImageSize[i] = InputImageSize[i] / factors[i];
			 }

			 ImageType::RegionType region;
		     region.SetSize(outputImageSize);
		     imagePtr->SetRegions(region);
		     imagePtr->Allocate();

			 //Setting The Origin
			 imagePtr->SetOrigin(m_InputImage->GetOrigin());
			 ImageType::SpacingType spacing;
			 spacing[0] = m_InputImage->GetSpacing()[0] * m_Schedule[ilevel][0];			 
			 spacing[1] = m_InputImage->GetSpacing()[1] * m_Schedule[ilevel][1];			 
			 spacing[2] = m_InputImage->GetSpacing()[2] * m_Schedule[ilevel][2];			 

			 imagePtr->SetSpacing(spacing);

			 itk::Image<float>::PixelContainer* outputPixelPointer = 
				 imagePtr->GetPixelContainer();

			 unsigned long levelLen = outputPixelPointer->Size();

			 /*std::cout<<"size for level "<<ilevel<<" = "<<
				 levelLen<<std::endl;*/

			 itk::Image<float>::PixelType* outputBufferPointer = 
			   imagePtr->GetBufferPointer();

			 if (ilevel == static_cast<int>(this->GetNumberOfLevels()) - 1)
			 {
				 inputBufferPointer = 
			     m_InputImage->GetBufferPointer();
			 }
			 else
			 {
			    inputBufferPointer = 
			     OutputList[ilevel + 1]->GetBufferPointer();
			 }

			 if( allOnes && ilevel == static_cast<int>(this->GetNumberOfLevels()) - 1 )
			 {
		       int len = InputImageSize[0] * InputImageSize[1] * InputImageSize[2];
		       memcpy(outputBufferPointer, inputBufferPointer, sizeof(int) * len);
			   imagePtr->Modified();
			   OutputList[ilevel] = imagePtr;
			 }
        
			 else
			 {
				 long outputIndex;
				 for (int ii=0;ii<levelLen;ii++)
				 {
					outputBufferPointer[ii] = 0.0;
				 }
				 //Find Output Points, Downsample and Smoothing
				 for (zIdxOutput = 1;zIdxOutput<outputImageSize[2]-1;zIdxOutput++)
				 {
					 for (yIdxOutput=1;yIdxOutput<outputImageSize[1]-1;yIdxOutput++)
					 {
						 for (xIdxOutput=1;xIdxOutput<outputImageSize[0]-1;xIdxOutput++)
						 {
							 double outputValue = CalculateOutputData();
						
							 //Writing Output Pixel						 
							 outputIndex = xIdxOutput + (yIdxOutput*outputImageSize[0]) +
								 (zIdxOutput*outputImageSize[0]*outputImageSize[1]);

							 outputBufferPointer[outputIndex] = outputValue;
						 }
					 }
				 }
				 imagePtr->Modified();
				 OutputList[ilevel] = imagePtr;
			 }//End Else
		 }   
    } //End For ilevel
}

/*
* PrintSelf method
*/
template <class TInputImage, class TOutputImage>
void
	RecursivePyramidFilter<TInputImage, TOutputImage>
	::PrintSelf(std::ostream& os, Indent indent) const
{
	Superclass::PrintSelf(os,indent);
}

template <class TInputImage, class TOutputImage>
void
	RecursivePyramidFilter<TInputImage, TOutputImage>
	::SetNumberOfLevels(unsigned long num)
{
	if( m_NumberOfLevels == num )
    { 
    return; 
    }
  
  this->Modified();

  // clamp value to be at least one
  m_NumberOfLevels = num;
  if( m_NumberOfLevels < 1 ) m_NumberOfLevels = 1;

  // resize the schedules
  ScheduleType temp( m_NumberOfLevels, ImageDimension );
  temp.Fill( 0 );
  m_Schedule = temp;

  // determine initial shrink factor
  unsigned int startfactor = 1;
  startfactor = startfactor << ( m_NumberOfLevels - 1 );

  // set the starting shrink factors
  this->SetStartingShrinkFactors( startfactor );
 
}

template <class TInputImage, class TOutputImage>
unsigned long
	RecursivePyramidFilter<TInputImage, TOutputImage>
	::GetNumberOfLevels()
{
	return m_NumberOfLevels;

}

template <class TInputImage, class TOutputImage>
typename RecursivePyramidFilter<TInputImage,TOutputImage>::OutputImagePointer
RecursivePyramidFilter<TInputImage, TOutputImage>
	::GetOutput(int level)
{
	return OutputList[level];
		
}

template <class TInputImage, class TOutputImage>
void
	RecursivePyramidFilter<TInputImage, TOutputImage>
	::SetSchedule(Array2D<unsigned int> schedule)
{
	m_Schedule = schedule;
}

template <class TInputImage, class TOutputImage>
Array2D<unsigned int>
	RecursivePyramidFilter<TInputImage, TOutputImage>
	::GetSchedule()
{
	return m_Schedule;
}

template <class TInputImage, class TOutputImage>
void
	RecursivePyramidFilter<TInputImage, TOutputImage> 
	::UpdateLargestPossibleRegion()
{
	this->GenerateData();
}

template <class TInputImage, class TOutputImage>
void
	RecursivePyramidFilter<TInputImage, TOutputImage> 
	::SetStartingShrinkFactors( unsigned int * factors)
{

  for( unsigned int dim = 0; dim < ImageDimension; ++dim )
    {
    m_Schedule[0][dim] = factors[dim];
    if( m_Schedule[0][dim] == 0 ) 
      {
      m_Schedule[0][dim] = 1;
      }
    }

  for( unsigned int level = 1; level < m_NumberOfLevels; ++level )
    {
    for( unsigned int dim = 0; dim < ImageDimension; ++dim )
      {
      m_Schedule[level][dim] = m_Schedule[level-1][dim] / 2;
      if( m_Schedule[level][dim] == 0 ) 
        {
        m_Schedule[level][dim] = 1;
        }
      }
    }

  this->Modified();


}

template <class TInputImage, class TOutputImage>
void
	RecursivePyramidFilter<TInputImage, TOutputImage> 
	::SetStartingShrinkFactors( unsigned int factor )
{

  unsigned int array[ImageDimension];
  for( unsigned int dim = 0; dim < ImageDimension; ++dim )
    {
    array[dim] = factor;
    }

  this->SetStartingShrinkFactors( array );

}

template <class TInputImage, class TOutputImage>
void
	RecursivePyramidFilter<TInputImage, TOutputImage> 
	::SetInput(InputImageConstPointer inputPointer)
{
	m_InputImage = inputPointer;
	
}

template <class TInputImage, class TOutputImage>
double
	RecursivePyramidFilter<TInputImage, TOutputImage> 
	::CalculateOutputData()
{
	long inputIndex;
	int xIdxInput;
    int yIdxInput;
	int zIdxInput;

	double outputValue = 0.0;
			
	 //Compute Equivalent Input points
	 //Smoothing and calculating Output Pixel Value
	 xIdxInput = xIdxOutput * factors[0];
	 yIdxInput = yIdxOutput * factors[1];
	 zIdxInput = zIdxOutput * factors[2];

	 //Computing the Kernal Values
	 ///////////////////////////////////////////////////////////
	 unsigned int kernelSum = 0;

	 for (int firstAxes=0; firstAxes<3;firstAxes++)
	 {
		 for (int secondAxes=0; secondAxes<3;secondAxes++)
		 {
			 for (int thirdAxes=0; thirdAxes<3;thirdAxes++)
			 {
				kernelSum = kernelSum + Kernel[firstAxes][secondAxes][thirdAxes];
				inputIndex = (xIdxInput+firstAxes-1) + 
				 ((yIdxInput+secondAxes-1)*InputImageSize[0]) 
				 + ((zIdxInput+thirdAxes-1)*InputImageSize[0]*InputImageSize[1]);

				 outputValue += inputBufferPointer[inputIndex] * 
				   Kernel[firstAxes][secondAxes][thirdAxes];
				
			 }
		 }
	 }

	 outputValue = outputValue / kernelSum;
	 return outputValue;
}

} // namespace itk


#pragma warning (pop)

#endif
