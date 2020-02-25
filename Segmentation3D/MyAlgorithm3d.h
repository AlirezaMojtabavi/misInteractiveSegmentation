
#pragma once
#include "./Segmentation3D/MySpeedFunction3D.h"
#include "ImageType.h"

using  misSpeedFunction3DType = MySpeedFunction3D< misInternalImageType, misInternalImageType >;

#define VTK_CREATE(type, name) \
  vtkSmartPointer<type> name = vtkSmartPointer<type>::New()

struct coordinate3D
{
	double _x;
	double _y;
	double _z;
};



class MyAlgorithm3d
{
public:


	MyAlgorithm3d(std::vector<misPixelType> intensity, std::vector<coordinate3D> seeds);
	void SetInternalImage(misInternalImageType::Pointer _InternalImage);

	void FastMarching(const double);
	void LevelSet(short int	 lower, short int upper, double edge, double weight);
	void LevelSet(double edge, double weight);
	double* GetROI();
 
	misInternalImageType* GetFastMarching();
	misOutputImageType*  GetThresholder();

private:
	//const unsigned short FillValue = 1000;
	misInternalImageType::Pointer IS_InternalImage;

	misSpeedFunction3DType::Pointer SegmentationSpeedFunction = misSpeedFunction3DType::New();

	ThresholdingFilterType::Pointer thresholder = ThresholdingFilterType::New();

	ThresholdSegmentationLevelSetImageFilterType::Pointer thresholdSegmentation = 
		ThresholdSegmentationLevelSetImageFilterType::New();

	std::vector<misPixelType> m_intensity;
	std::vector<coordinate3D> m_Seeds;
	FastMarchingFilterType::Pointer  fastMarching = FastMarchingFilterType::New();
	NodeContainer::Pointer seeds = NodeContainer::New();

	misOutputImageType::Pointer result = misOutputImageType::New();

	double ROI[6];
};