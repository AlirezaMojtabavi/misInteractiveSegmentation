#pragma once
const  unsigned int  Dimension = 3;

typedef  float  misInternalPixelType;
typedef itk::Image< misInternalPixelType, Dimension >  misInternalImageType;
typedef itk::Image< float, Dimension > ITKImageType;

typedef float misOutputPixelType;
typedef itk::Image< misOutputPixelType, Dimension > misOutputImageType;

typedef itk::CastImageFilter<ITKImageType, misInternalImageType> ImageType_2_InternalType;


typedef  itk::FastMarchingImageFilter< misInternalImageType, misInternalImageType > FastMarchingFilterType;
typedef FastMarchingFilterType::NodeContainer   NodeContainer;
typedef FastMarchingFilterType::NodeType    NodeType;
typedef  itk::ThresholdSegmentationLevelSetImageFilter< misInternalImageType, misInternalImageType, misOutputPixelType>
ThresholdSegmentationLevelSetImageFilterType;
typedef itk::BinaryThresholdImageFilter<misInternalImageType, misOutputImageType> ThresholdingFilterType;
typedef MySpeedFunction3D< misInternalImageType, misInternalImageType > MySpeedFunction3DType;
