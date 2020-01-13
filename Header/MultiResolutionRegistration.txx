#ifndef _MultiResolutionRegistration_txx
#define _MultiResolutionRegistration_txx

#include "MultiResolutionRegistration.h"
//#include <process.h>


template < class TInputPixel, class TInputImage, class TImage>
itk::FixedArray<unsigned int, TInputImage::ImageDimension>  
MultiResolutionRegistration<TInputPixel, TInputImage, TImage>::
ConvertPermuteOrder(itk::Matrix<int,TInputImage::ImageDimension,TInputImage::ImageDimension> 
					inputMatrix)
{
	itk::FixedArray<unsigned int, TInputImage::ImageDimension> permuteOrder;
	for (int i=0;i<TInputImage::ImageDimension;i++)
	{
		bool findElement = false;
		for (int j=0;j<TInputImage::ImageDimension;j++)
		{
			if ((inputMatrix(i,j) == 1) || (inputMatrix(i,j) == -1))
			{
				findElement = true;
				permuteOrder[i] = j;
			}
		}
		if (!findElement)
		{
			permuteOrder[i] = i;
		}
	}
	return permuteOrder;
}


template < class TInputPixel, class TInputImage, class TImage>
itk::FixedArray<bool, TInputImage::ImageDimension>  
MultiResolutionRegistration<TInputPixel, TInputImage, TImage>::
ConvertFlipOrder(itk::Matrix<int,TInputImage::ImageDimension,TInputImage::ImageDimension> 
				 inputMatrix)
{
	itk::FixedArray<bool, TInputImage::ImageDimension> FlipOrder;
	FlipOrder.Fill(false);
	for (int i=0;i<TInputImage::ImageDimension;i++)
	{
		for (int j=0;j<TInputImage::ImageDimension;j++)
		{
			if (inputMatrix(i,j) == -1)
			{
				FlipOrder[i] = true;
			}
		}
	}
	return FlipOrder;
}

template < class TInputPixel, class TInputImage, class TImage>
HANDLE MultiResolutionRegistration<TInputPixel, TInputImage, TImage>::
CallExecute_SeprateThread()
{
	unsigned uiThread1ID;

	HANDLE hth1 = (HANDLE)_beginthreadex( NULL,  0, 
		this->ThreadStaticEntryPoint, this, 0, &uiThread1ID );
	
	return hth1;
}

template < class TInputPixel, 
class TInputImage ,
class TImage >
	void MultiResolutionRegistration<TInputPixel, TInputImage, TImage>::SetMovingPyramid( ImagePyramidType* MovingPyramid )
{
	this->m_Registrator->SetMovingPyramid(MovingPyramid);
}

template < class TInputPixel, 
class TInputImage,
class TImage  >
	void MultiResolutionRegistration<TInputPixel, TInputImage, TImage>::SetFixedPyramid( ImagePyramidType* FixedPyramid )
{
	this->m_Registrator->SetFixedPyramid(FixedPyramid);
}


template < class TInputPixel, 
class TInputImage,
class TImage>
	void MultiResolutionRegistration<TInputPixel, TInputImage, TImage>::SetFixedImageRegionPyramid( std::vector<FixedImageRegionType> fixedRegion )
{
	this->m_Registrator->SetFixedImageRegionPyramid(fixedRegion);
}


#endif