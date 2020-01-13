#pragma once
#include "IRegionGrowing.h"

MOCK_BASE_CLASS(MockRegionGrowing, IRegionGrowing)
{
	MOCK_NON_CONST_METHOD(AddSeed, 3, void(int i, int j, int k));
	MOCK_NON_CONST_METHOD(AddSeedPosition, 1, void(const double *position));
	MOCK_NON_CONST_METHOD(UpdateMaximumObjectValidityWithoutROI, 0, bool());
	MOCK_NON_CONST_METHOD(UpdateMaximumObjectValidityWithROI, 0, bool());
	MOCK_NON_CONST_METHOD(Calculation, 0, bool());
	MOCK_NON_CONST_METHOD(CancelSegmentationStatus, 0, bool());
	MOCK_NON_CONST_METHOD(ResetSetting, 0, void());
	MOCK_NON_CONST_METHOD(ResetMaximumObjectValidRange, 0, void());
	MOCK_NON_CONST_METHOD(SetImage, 1, void(vtkImageData *input_image));
	MOCK_NON_CONST_METHOD(SetMaximumObjectValidity, 1, void(double extent[6]));
	MOCK_NON_CONST_METHOD(LimitBoundaryPosition, 1, void(double * spacing));
	MOCK_NON_CONST_METHOD(ClearSeeds, 0, void());
	MOCK_NON_CONST_METHOD(ExtractBorderOn, 0, void());
	MOCK_NON_CONST_METHOD(ExtractBorderOff, 0, void());
	MOCK_NON_CONST_METHOD(SetLowerThreshold, 1, void(int lowerThreshold));
	MOCK_NON_CONST_METHOD(SetHigherThreshold, 1, void(int higherThreshold));
	MOCK_NON_CONST_METHOD(SetMargineValue, 1, void(misRGObjectType margineType));
	MOCK_NON_CONST_METHOD(RequestCancelSegmentation, 0, void());
	MOCK_NON_CONST_METHOD(SetThresholdChecking, 1, void(bool));
	MOCK_NON_CONST_METHOD(GetBorders, 0, int*());
	MOCK_NON_CONST_METHOD(GetRegionGrowingState, 0, RGState());
	MOCK_NON_CONST_METHOD(GetSegmentedOutputImage, 0, vtkSmartPointer<vtkImageData>());
	MOCK_NON_CONST_METHOD(SetNumberOfMargineVoxel, 1, void(int voxelNum));
	MOCK_NON_CONST_METHOD(SetDistanceFromMargine, 1, void(double distance));
	MOCK_NON_CONST_METHOD(ApplyMarginalBorder, 0, void());
	MOCK_NON_CONST_METHOD(ExtractBorders, 0, void());
	MOCK_CONST_METHOD(GetMutex, 0, HANDLE());
	MOCK_CONST_METHOD(GetLowerThreshold, 0, int());
	MOCK_CONST_METHOD(GetHigherThreshold, 0, int());
	MOCK_NON_CONST_METHOD(ApplyMarginToImage, 2, void(vtkSmartPointer<vtkImageData> currentImage, double MarginValue));
};

#pragma once
