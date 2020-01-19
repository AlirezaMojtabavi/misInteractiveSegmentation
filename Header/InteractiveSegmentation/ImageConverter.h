#pragma once

#include"vtkSmartPointer.h"
#include "itkSmartPointer.h"
#include <itkImage.h>
#include <itkVTKImageToImageFilter.h>
#include <itkImageToVTKImageFilter.h>

const  unsigned int  Dimension = 3;
typedef  float  InternalPixelType;
typedef itk::Image< InternalPixelType, Dimension >  InternalImageType;

typedef itk::Image <unsigned  short, Dimension > ImageType;

typedef unsigned short OutputPixelType;
typedef itk::Image< OutputPixelType, Dimension > OutputImageType;

typedef itk::VTKImageToImageFilter<ImageType> VTKImageToImageType;



class ImageConverter
{
public:
	static ImageType::Pointer GetITKFromVTK(vtkSmartPointer<vtkImageData> );
static 	InternalImageType::Pointer GetInternalImage(vtkSmartPointer<vtkImageData>  _ResliceDicom3D);
 
};

