#pragma once
#ifndef _MISVOLUMEEXTRACTOR_
#define _MISVOLUMEEXTRACTOR_

#include "misObject.h"

struct GetVolumeWidget
	{
		vtkImageData* m_WidgetInput;
		vtkVolume*  m_volume;
		vtkVolumeRayCastMapper* m_volume_mapper;
	};
class misVolumeExtractor : public misObject
{
public:

misVolumeExtractor(void)
	{
	}

public:
	
	typedef itk::Image<float,3>  ImageType;
	typedef vtkImageData* vtkImageType;
	typedef itk::ImageFileReader< ImageType > VolumeReaderType;
	typedef itk::ImageRegionConstIterator< ImageType > ConstIteratorType;
	typedef itk::ImageRegionIterator< ImageType>       IteratorType;
public:
	igstkStandardClassBasicTraitsMacro( misVolumeExtractor, misObject)  
	
	GetVolumeWidget GetVolume(const std::string FileName);
	GetVolumeWidget GetVolume(misVolumeExtractor::ImageType::Pointer ImageName);
	vtkImageData* GetvtkImage(misVolumeExtractor::ImageType::Pointer ImageName);
	vtkImageData* GetvtkImage(const std::string FileName);
	
	vtkImageData* WidgetInput;

	

	VolumeReaderType::Pointer reader;
	vtkVolume* volume;

    ImageType::Pointer   res;
	vtkImageData*  pImage;
	/*ImageType::SizeType  size;*/
	vtkImageCast* FixedImagecast;

	
	ImageType::IndexType startindex;
	ImageType::RegionType region;
	
};
#endif



