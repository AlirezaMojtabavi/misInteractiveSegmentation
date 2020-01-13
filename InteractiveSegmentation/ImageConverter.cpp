#include "pch.h"
#include "ImageConverter.h"

ImageType::Pointer ImageConverter::GetITKFromVTK(vtkSmartPointer<vtkImageData> image)
{
	VTKImageToImageType::Pointer VTKImageToImage = VTKImageToImageType::New();
	VTKImageToImage->SetInput(image);
	auto ITKImage = VTKImageToImage->GetOutput();
	ITKImage->Update();
	return ITKImage;
}

InternalImageType::Pointer ImageConverter::GetInternalImage(vtkSmartPointer<vtkImageData> image)
{
	auto imageType = image->GetScalarType();
	VTKImageToImageType::Pointer ITKImage = VTKImageToImageType::New();
	ITKImage->SetInput(image);
	ITKImage->Update();
	typedef itk::CastImageFilter<ImageType, InternalImageType> ImageType_2_InternalType;
	ImageType_2_InternalType::Pointer Image_2_Internal = ImageType_2_InternalType::New();
	Image_2_Internal->SetInput(ITKImage->GetOutput());
	Image_2_Internal->Update();
	auto InternalImage = Image_2_Internal->GetOutput();
	return InternalImage;
}
