
#pragma once
#include "MySpeedFunction3D.h"
#include "imagetype.h"


#define VTK_CREATE(type, name) \
  vtkSmartPointer<type> name = vtkSmartPointer<type>::New()

struct coordinate3D
{
	double _x;
	double _y;
	int _z;
};



class MyAlgorithm3d
{
public:


	MyAlgorithm3d(std::vector<unsigned short> intensity, std::vector<coordinate3D> seeds);
	void SetInternalImage(misInternalImageType::Pointer _InternalImage);

 
	void SetSpeedFunction(itk::SmartPointer<misSpeedFunction3DType>);

	void FastMarching(const double);
	void LevelSet(int lower, int upper, double edge, double weight);
	void LevelSet(double edge, double weight);

 
	misInternalImageType* GetFastMarching();
	misOutputImageType*  GetThresholder();

private:

	misInternalImageType::Pointer IS_InternalImage;

	//itk::ThresholdSegmentationLevelSetFunction<misOutputImageType>::Pointer SegmentationSpeedFunction =
		//MySpeedFunction3DType::New();

	misSpeedFunction3DType::Pointer SegmentationSpeedFunction;

	ThresholdingFilterType::Pointer thresholder = ThresholdingFilterType::New();


	ThresholdSegmentationLevelSetImageFilterType::Pointer thresholdSegmentation = 
		ThresholdSegmentationLevelSetImageFilterType::New();

	std::vector<unsigned short> m_intensity;
	std::vector<coordinate3D> m_Seeds;
	FastMarchingFilterType::Pointer  fastMarching = FastMarchingFilterType::New();
	NodeContainer::Pointer seeds = NodeContainer::New();
};