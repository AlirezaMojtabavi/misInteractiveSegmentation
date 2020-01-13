#pragma once
#include "misEnums.h"
#include "vtkImageData.h"
#include "misAnalysisStudioTypes.h"
class IRegionGrowing
{
public:
	virtual void AddSeed(int i, int j, int k) = 0;
	virtual void AddSeedPosition(const double *position) = 0;
	virtual bool UpdateMaximumObjectValidityWithoutROI(void) = 0;
	virtual bool UpdateMaximumObjectValidityWithROI(void) = 0;
	virtual bool Calculation(void) = 0;
	virtual bool CancelSegmentationStatus(void) = 0;
	virtual void ResetSetting(void) = 0;
	virtual void ResetMaximumObjectValidRange() = 0;
	virtual void SetImage(vtkImageData *input_image) = 0;
	virtual void SetMaximumObjectValidity(double extent[6]) = 0;
	virtual void LimitBoundaryPosition(double * spacing) = 0;
	virtual void ClearSeeds(void) = 0;
	virtual void ExtractBorderOn(void) = 0;
	virtual void ExtractBorderOff(void) = 0;
	virtual void  SetLowerThreshold(int lowerThreshold) = 0;
	virtual void  SetHigherThreshold(int higherThreshold) = 0;
	virtual void SetMargineValue(misRGObjectType margineType) = 0;
	virtual void RequestCancelSegmentation(void) = 0;
	virtual void SetThresholdChecking(bool) = 0;
	virtual int* GetBorders() = 0;
	virtual RGState  GetRegionGrowingState(void) = 0;
	virtual vtkSmartPointer<vtkImageData> GetSegmentedOutputImage() = 0;
 	virtual void SetNumberOfMargineVoxel(int voxelNum) = 0;//
	virtual void SetDistanceFromMargine(double distance) = 0;
	virtual void ApplyMarginalBorder()=0;
	virtual void ExtractBorders()=0;
	virtual HANDLE GetMutex() const = 0;
	virtual int GetLowerThreshold() const = 0;
	virtual int GetHigherThreshold() const= 0;
	virtual void ApplyMarginToImage(vtkSmartPointer<vtkImageData> currentImage, double MarginValue) = 0;

 };
