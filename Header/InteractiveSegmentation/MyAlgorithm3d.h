
#pragma once

#include<vector>
#include "vtkObjectFactory.h"
#include "itkFastMarchingImageFilter.h"
#include "itkBinaryThresholdImageFilter.h"
#include "itkZeroCrossingImageFilter.h"
#include "itkThresholdSegmentationLevelSetImageFilter.h"
#include "itkNumericSeriesFileNames.h"
#include "MySpeedFunction3D.h"
#include "MyInteractionStyle3D.h"

#include "ImageConverter.h"
#include "SeedList.h"



class MyAlgorithm3d
{
public:


	MyAlgorithm3d(InternalImageType::Pointer _InternalImage, SeedList list);



	typedef MySpeedFunction3D< InternalImageType, InternalImageType > MySpeedFunction3DType;
	void Set_Function(itk::SmartPointer<MySpeedFunction3DType>);

	void FastMarching(const double);
	void Level_Set(int lower, int upper, double edge, double weight);
	void Level_Set(double edge, double weight);


	InternalImageType* Get_FastMarching();
	OutputImageType*  Get_thresholder();

private:

	InternalImageType::Pointer IS_InternalImage = InternalImageType::New();
	SeedList IS_SeedList;

	MySpeedFunction3DType::Pointer my_function = MySpeedFunction3DType::New();

	typedef itk::BinaryThresholdImageFilter<InternalImageType, OutputImageType> ThresholdingFilterType;
	ThresholdingFilterType::Pointer thresholder = ThresholdingFilterType::New();

	typedef  itk::ThresholdSegmentationLevelSetImageFilter< InternalImageType, InternalImageType >
		ThresholdSegmentationLevelSetImageFilterType;
	ThresholdSegmentationLevelSetImageFilterType::Pointer thresholdSegmentation = 
		ThresholdSegmentationLevelSetImageFilterType::New();

	typedef  itk::FastMarchingImageFilter< InternalImageType, InternalImageType > FastMarchingFilterType;
	typedef FastMarchingFilterType::NodeContainer   NodeContainer;
	typedef FastMarchingFilterType::NodeType    NodeType;
	FastMarchingFilterType::Pointer  fastMarching = FastMarchingFilterType::New();
	NodeContainer::Pointer seeds = NodeContainer::New();
};