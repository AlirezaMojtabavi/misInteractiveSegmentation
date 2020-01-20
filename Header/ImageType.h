#pragma once
const  unsigned int  Dimension = 3;

typedef  float  misInternalPixelType;
typedef itk::Image< misInternalPixelType, Dimension >  misInternalImageType;// input algorithm
typedef itk::Image< unsigned short, Dimension > ITKImageType;
//typedef itk::Image< unsigned short, Dimension > inputImageType;

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
typedef MySpeedFunction3D< misInternalImageType, misInternalImageType > misSpeedFunction3DType;
typedef itk::VTKImageToImageFilter<ITKImageType> VTKImageToImageType;
//typedef itk::CastImageFilter<ITKImageType, misInternalImageType>;