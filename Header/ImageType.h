
#pragma once
const  unsigned int  Dimension = 3;

typedef  unsigned short misPixelType;
typedef  float  misInternalPixelType;

typedef itk::Image< misInternalPixelType, Dimension >  misInternalImageType;// input algorithm
typedef itk::Image<misPixelType, Dimension > ITKImageType;
typedef unsigned short misOutputPixelType;
typedef itk::Image< misOutputPixelType, Dimension > misOutputImageType; //output algorithm

typedef itk::CastImageFilter<ITKImageType, misInternalImageType> ITKImageType_2_InternalType;
typedef itk::CastImageFilter<misOutputImageType, misInternalImageType> OutputType_2_InternalType;

typedef  itk::FastMarchingImageFilter< misInternalImageType, misInternalImageType > FastMarchingFilterType;
typedef FastMarchingFilterType::NodeContainer   NodeContainer;
typedef FastMarchingFilterType::NodeType    NodeType;
typedef  itk::ThresholdSegmentationLevelSetImageFilter< misInternalImageType, misInternalImageType>
	ThresholdSegmentationLevelSetImageFilterType;
typedef itk::BinaryThresholdImageFilter<misInternalImageType, misOutputImageType> ThresholdingFilterType;
typedef itk::VTKImageToImageFilter<ITKImageType> VTKImageToImageType;
//typedef itk::CastImageFilter<ITKImageType, misInternalImageType>;