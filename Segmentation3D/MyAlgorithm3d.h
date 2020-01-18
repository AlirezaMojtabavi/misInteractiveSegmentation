
#pragma once

#include<vector>

#include "MySpeedFunction3D.h"
const  unsigned int  Dimension = 3;
typedef  float  InternalPixelType;
typedef itk::Image< InternalPixelType, Dimension >  InternalImageType;

typedef itk::Image < unsigned short, Dimension > ITKImageType;

typedef unsigned short OutputPixelType;
typedef itk::Image< OutputPixelType, Dimension > OutputImageType;

#define VTK_CREATE(type, name) \
  vtkSmartPointer<type> name = vtkSmartPointer<type>::New()

struct coordinate3D
{
	double _x;
	double _y;
	int _z;
};

typedef itk::VTKImageToImageFilter<ITKImageType> VTKImageToImageType;
typedef itk::CastImageFilter<ITKImageType, InternalImageType> ImageType_2_InternalType;


typedef  itk::FastMarchingImageFilter< InternalImageType, InternalImageType > FastMarchingFilterType;
typedef FastMarchingFilterType::NodeContainer   NodeContainer;
typedef FastMarchingFilterType::NodeType    NodeType;



class MyAlgorithm3d
{
public:


	MyAlgorithm3d(std::vector<unsigned short> intensity, std::vector<coordinate3D> seeds);
	void SetInternalImage(InternalImageType::Pointer _InternalImage);

 
	typedef MySpeedFunction3D< InternalImageType, InternalImageType > MySpeedFunction3DType;
	void SetSpeedFunction(itk::SmartPointer<MySpeedFunction3DType>);

	void FastMarching(const double);
	void LevelSet(int lower, int upper, double edge, double weight);
	void LevelSet(double edge, double weight);

 
	InternalImageType* GetFastMarching();
	OutputImageType*  GetThresholder();

private:

	InternalImageType::Pointer IS_InternalImage;

	MySpeedFunction3DType::Pointer SegmentationSpeedFunction = MySpeedFunction3DType::New();

	typedef itk::BinaryThresholdImageFilter<InternalImageType, OutputImageType> ThresholdingFilterType;
	ThresholdingFilterType::Pointer thresholder = ThresholdingFilterType::New();

	typedef  itk::ThresholdSegmentationLevelSetImageFilter< InternalImageType, InternalImageType >
		ThresholdSegmentationLevelSetImageFilterType;
	ThresholdSegmentationLevelSetImageFilterType::Pointer thresholdSegmentation = 
		ThresholdSegmentationLevelSetImageFilterType::New();

	std::vector<unsigned short> m_intensity;
	std::vector<coordinate3D> m_Seeds;
	FastMarchingFilterType::Pointer  fastMarching = FastMarchingFilterType::New();
	NodeContainer::Pointer seeds = NodeContainer::New();
};