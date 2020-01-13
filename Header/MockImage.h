#pragma once
#include "IImage.h"
#include "misStrctPatientData.h"
#include "misImageIOProperties.h"
#include "misImageViewingItemsStruct.h"
#include "misGuiStructures.h"

MOCK_BASE_CLASS(MockImage, IImage)
{

	MOCK_CONST_METHOD(GetUID, 0, std::string()); // return a unique identifier string 
	MOCK_NON_CONST_METHOD(SetUID, 1, void(const std::string&));
	MOCK_NON_CONST_METHOD(DeepCopy, 1, void(std::shared_ptr<IImage>));
	MOCK_NON_CONST_METHOD(Update, 0, void());
	MOCK_NON_CONST_METHOD(SetName, 1, void(std::string));
	MOCK_NON_CONST_METHOD(GetName, 0, std::string());
	MOCK_NON_CONST_METHOD(GetROI, 0, misROI());
	MOCK_NON_CONST_METHOD(GetWorldDiemension, 0, misROI());
	MOCK_NON_CONST_METHOD(GetConfirmedDirectionTransform, 0, vtkTransform*  (void));
	MOCK_NON_CONST_METHOD(GetScalerRangeNeeded, 0, std::vector<double>(void));
	MOCK_CONST_METHOD(GetImageModality, 0, misImageDataModality(void));
	MOCK_NON_CONST_METHOD(SetPrimeryUID, 1, void(misUID));
	MOCK_NON_CONST_METHOD(GetPrimeryUID, 0, misUID());
	// TODO: uncompleted
	MOCK_NON_CONST_METHOD(SetImageProperties, 1, misResultCode::ResultIds(misImageDataProperties*));
	// all Image properties
	MOCK_NON_CONST_METHOD(GetImageProperties, 0, misImageDataProperties* (void));
	MOCK_NON_CONST_METHOD(SetResterictedPatientProperties, 1, misResultCode::ResultIds(misPatientProperties));
	//  use for saving image properties in Data Layer
	MOCK_NON_CONST_METHOD(GetImageIOProperties, 0, misImageIOProperties(void));
	MOCK_NON_CONST_METHOD(GetViewingStrct, 0, misImageViewingItemsStruct(void));
	MOCK_NON_CONST_METHOD(GetObjectType, 0, MisObjectType());
	MOCK_NON_CONST_METHOD(GetViewingProperties, 0, misWindowLevelStr());
	MOCK_NON_CONST_METHOD(GetViewingPropertiesDefault, 0, misWindowLevelStr());
	MOCK_NON_CONST_METHOD(GetViewingPropertiesMaxRange, 0, misWindowLevelStr());
	// use for viewing in the GUI
	MOCK_NON_CONST_METHOD(GetSimplifiedProperties, 0, misDicomDataViewingProperties(void));

	MOCK_NON_CONST_METHOD(ResetConfirmedTransform, 0, void(void));

	// Some time image instead of axial is coronal or sagittal, or even mirrored. correctionMatrix corrects the image
	MOCK_NON_CONST_METHOD(SetConfirmedDirectionTransform, 1, void(vtkMatrix4x4*));
	MOCK_NON_CONST_METHOD(SetROI, 1, bool(const misROI&));
	//MOCK_NON_CONST_METHOD void DeepCopyOnlyImagePropeties( std::shared_ptr<IImage> image)  ); ;
	MOCK_NON_CONST_METHOD(SetDuplicatedRangeActivation, 1, void(bool));
	MOCK_NON_CONST_METHOD(SetViewingProperties, 2, void(misImageViewingType, misWindowLevelStr));
	MOCK_NON_CONST_METHOD(SetSkinThreashold, 1, void(double));
	MOCK_NON_CONST_METHOD(SetBoneThreshold, 1, void(double));
	MOCK_NON_CONST_METHOD(SetTeethThreshold, 1, void(double));
	MOCK_NON_CONST_METHOD(GetDeafaultSkinThreshold, 0, boost::optional<double>(void));
	MOCK_NON_CONST_METHOD(GetCurrentVisibleSurfaceThreshold, 1, double(misApplicationType appType));
	MOCK_NON_CONST_METHOD(GetCurrentBoneThreshold, 0, boost::optional<double>(void));
	MOCK_NON_CONST_METHOD(GetCurrentTeethThreshold, 0, boost::optional<double>(void));
	MOCK_NON_CONST_METHOD(GetCurrentSkinThreshold, 0, boost::optional<double>());
	MOCK_NON_CONST_METHOD(GetImageCenter, 0, parcast::PointD3());
	MOCK_NON_CONST_METHOD(GetDuplicatedRangeActivation, 0, bool(void));
	MOCK_NON_CONST_METHOD(CheckPrimaryConditionOnImageGeometry, 0, bool());
	MOCK_CONST_METHOD(GetBinaryFileName, 0, std::string());
	MOCK_NON_CONST_METHOD(SetBinaryFileName, 1, void(std::string));
	MOCK_NON_CONST_METHOD(GetDimensions, 0, int*());
	MOCK_NON_CONST_METHOD(GetScalarPointer, 0, void*());
	MOCK_NON_CONST_METHOD(GetScalarType, 0, int());
	MOCK_NON_CONST_METHOD(GetSpacing, 0, double* ());
	MOCK_NON_CONST_METHOD(Modified, 0, void());
	MOCK_CONST_METHOD(GetRawImageData, 0, vtkSmartPointer<vtkImageData>());
	MOCK_NON_CONST_METHOD(SetRawImageData, 1, void(vtkSmartPointer<vtkImageData>));
	MOCK_CONST_METHOD(GetModificationFlag, 0, bool());
	MOCK_NON_CONST_METHOD(SetModificationFlag, 1, void(bool));
	MOCK_CONST_METHOD(GetModificationFlagBinariesPart, 0, bool());
	MOCK_NON_CONST_METHOD(SetModificationFlagBinariesPart, 1, void(bool));;
	MOCK_CONST_METHOD(GetConfirmedDirection, 0, bool());
	MOCK_NON_CONST_METHOD(SetConfirmedDirection, 1, void(bool));
	MOCK_CONST_METHOD(GetParentImageUID, 0, misUID());
	MOCK_NON_CONST_METHOD(SetParentImageUID, 1, void(misUID));
	MOCK_CONST_METHOD(GetViewingNameCompletenessStatus, 0, bool());
	MOCK_NON_CONST_METHOD(SetViewingNameCompletenessStatus, 1, void(bool));
	MOCK_NON_CONST_METHOD(GetImageDataProperties, 0, misImageDataProperties*  (void));
};
