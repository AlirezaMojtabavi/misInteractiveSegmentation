#ifndef __misItktoVtkimage_h
#define __misItktoVtkimage_h

class vtkImageCast;

class misItktoVtkimage
{
	typedef float InputPixelType;
	typedef float OutputPixelType;
	typedef float PixelType;
	typedef vtkImageData OutputImageType;
	typedef itk::Image< InputPixelType, 3 > InputImageType;
	typedef itk::Image< InputPixelType, 3 > itkInputImageType;
	typedef itk::ImageToVTKImageFilter <InputImageType> ConnectorType;
	typedef itk::CastImageFilter <itkInputImageType, OutputImageType > CastFilterType;

public:

	static void ConvertInToOut(InputImageType::Pointer inputImage,OutputImageType** outImage);

	~misItktoVtkimage()
	{
	}
};

#endif
