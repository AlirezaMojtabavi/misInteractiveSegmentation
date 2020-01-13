#pragma once

#include "vnl/vnl_matrix.h"
#include "itkArray.h"
#include "itkFixedArray.h"
#include "itkArray2D.h"
#include "itkMacro.h"
#include "itkImage.h"

namespace itk
{
	template <	class TInputImage,class TOutputImage>
	class ITK_EXPORT RecursivePyramidFilter : public ProcessObject
	{
	public:

		/** Standard class typedefs. */
		typedef RecursivePyramidFilter  Self;
		typedef SmartPointer<Self>  Pointer;
		typedef SmartPointer<const Self>  ConstPointer;

		/** Method for creation through the object factory. */
		itkNewMacro(Self);

		/** ImageDimension enumeration. */
		itkStaticConstMacro(ImageDimension, unsigned int,
			TInputImage::ImageDimension);

		/** Inherit types from the superclass.. */
		typedef TInputImage InputImageType;
		typedef TOutputImage OutputImageType;
		typedef typename InputImageType::Pointer InputImagePointer;
		typedef typename OutputImageType::Pointer OutputImagePointer;
		typedef typename InputImageType::ConstPointer InputImageConstPointer;

		//APIs Called in itkMultiResolutionImageRegistrationMethod
		OutputImagePointer GetOutput(int);
		void SetNumberOfLevels(unsigned long);
		void SetSchedule(Array2D<unsigned int>);
		void SetInput(InputImageConstPointer);
		void UpdateLargestPossibleRegion();
		Array2D<unsigned int> GetSchedule();
		unsigned long GetNumberOfLevels();

		void SetStartingShrinkFactors( unsigned int factor );
		void SetStartingShrinkFactors( unsigned int* factors );
		InputImageConstPointer GetImage()
		{
			InputImageConstPointer temp = 0;
			if(this->m_InputImage)
				return this->m_InputImage;
			else
				return temp;
		}
		/** Get the starting shrink factors */
		const unsigned int * GetStartingShrinkFactors() const;

	protected:
		RecursivePyramidFilter();
		~RecursivePyramidFilter() {};
		void PrintSelf(std::ostream&os, Indent indent) const;

		/** Generate the output data. */
		void GenerateData();

		//Calculating output value for one pixel
		double CalculateOutputData();

	private:
		RecursivePyramidFilter(const Self&); //purposely not implemented
		void operator=(const Self&); //purposely not implemented

		unsigned long m_NumberOfLevels;
		typedef Array2D<unsigned int> ScheduleType;

		ScheduleType m_Schedule;

		InputImageConstPointer m_InputImage;

		FixedArray<OutputImagePointer, 10> OutputList;

		double Kernel[3][3][3];

		int xIdxOutput, yIdxOutput, zIdxOutput;

		unsigned int factors[ImageDimension];

		typedef itk::Image<float,3> ImageType;
		//ImageType::SizeType inputImageSize;
		ImageType::SizeType InputImageSize;
		const itk::Image<float>::PixelType* inputBufferPointer;
	};

} // namespace itk

#ifndef ITK_MANUAL_INSTANTIATION
#include "RecursivePyramidFilter.txx"
#endif
 
