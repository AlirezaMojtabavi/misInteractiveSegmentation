#pragma once

#include "ICoordinateSystem.h"
#include "misResultCode.h"
#include "BusinessEntities/point.h"

struct misVisualizationSetting;
class misImageDataProperties;
class misImageIOProperties;
class misROI;
class misWindowLevelStr;

struct misImageViewingItemsStruct;
struct misPatientProperties;
struct misDicomDataViewingProperties;

enum misImageDataModality;
enum MisObjectType;
enum misImageViewingType;
enum misApplicationType;
enum misImageViewingType;

typedef std::string misUID;

class IImage : public ICoordinateSystem
{
public:

	virtual void SetUID(const std::string& id) = 0;
	virtual void DeepCopy(std::shared_ptr<IImage> image) = 0;
	virtual void Update() = 0;
	virtual void SetName(std::string name) = 0;
	virtual std::string GetName() = 0;
	virtual misROI GetROI() = 0;
	virtual misROI GetWorldDiemension() = 0;
	virtual vtkTransform*  GetConfirmedDirectionTransform() = 0;
	virtual std::vector<double>   GetScalerRangeNeeded() = 0;
	virtual misImageDataModality GetImageModality() const = 0;
	virtual void SetPrimeryUID(misUID uid) = 0;
	virtual misUID GetPrimeryUID() = 0;
	// TODO: uncompleted
	virtual misResultCode::ResultIds SetImageProperties(misImageDataProperties*  imageProperties) = 0;
	// all Image properties
	virtual misImageDataProperties*  GetImageDataProperties() = 0;
	virtual misResultCode::ResultIds SetResterictedPatientProperties(misPatientProperties  patientProperties) = 0;
	//  use for saving image properties in Data Layer
	virtual misImageIOProperties GetImageIOProperties() = 0;
	virtual misImageViewingItemsStruct GetViewingStrct() = 0;
	virtual MisObjectType GetObjectType() = 0;

	// use for viewing in the GUI
	virtual misDicomDataViewingProperties GetSimplifiedProperties() = 0;

	virtual void ResetConfirmedTransform() = 0;

	// Some time image instead of axial is coronal or sagittal, or even mirrored. correctionMatrix corrects the image
	virtual void SetConfirmedDirectionTransform(vtkMatrix4x4* correctionMatrix) = 0;
	virtual bool SetROI(const misROI &roi) = 0;
	//virtual void DeepCopyOnlyImagePropeties( std::shared_ptr<IImage> image)   = 0 ;
	virtual void SetDuplicatedRangeActivation(bool val) = 0;
	virtual void SetViewingProperties(misImageViewingType viewingType, misWindowLevelStr winlevStr) = 0;
	virtual void SetSkinThreashold(double threshold) = 0;
	virtual void SetBoneThreshold(double threshold) = 0;
	virtual void SetTeethThreshold(double threshold) = 0;
	virtual boost::optional<double> GetCurrentSkinThreshold() = 0;
	virtual boost::optional<double> GetDeafaultSkinThreshold() = 0;
 	
	virtual boost::optional<double> GetCurrentBoneThreshold() = 0;
	virtual boost::optional<double> GetCurrentTeethThreshold() = 0;
	virtual parcast::PointD3 GetImageCenter() = 0;
	virtual bool GetDuplicatedRangeActivation() = 0;
	virtual bool CheckPrimaryConditionOnImageGeometry() = 0;
	virtual std::string GetBinaryFileName() const = 0;
	virtual void SetBinaryFileName(std::string val) = 0;
	virtual int* GetDimensions() = 0;
	virtual void* GetScalarPointer() = 0;
	virtual int GetScalarType() = 0;
	virtual double* GetSpacing() = 0;
	virtual void Modified() = 0;
	virtual vtkSmartPointer<vtkImageData> GetRawImageData() const = 0;
	virtual void SetRawImageData(vtkSmartPointer<vtkImageData> val) = 0;
	virtual bool GetModificationFlag() const = 0;
	virtual void SetModificationFlag(bool val) = 0;
	virtual bool GetModificationFlagBinariesPart() const = 0;
	virtual void SetModificationFlagBinariesPart(bool val) = 0;
	virtual bool GetConfirmedDirection() const = 0;
	virtual void SetConfirmedDirection(bool val) = 0;
	virtual misUID GetParentImageUID() const = 0;
	virtual void SetParentImageUID(misUID val) = 0;
	virtual bool GetViewingNameCompletenessStatus() const = 0;
	virtual void SetViewingNameCompletenessStatus(bool val) = 0;
};

double GetRenderingNormalizedThreshold(std::shared_ptr<IImage> image, misApplicationType appType, const misVisualizationSetting& visulaizationSetting);

double GetCurrentVisibleSurfaceThreshold(std::shared_ptr<IImage> image, misApplicationType appType, const misVisualizationSetting& visulaizationSetting);