#pragma once

#include "IImage.h"
#include "misROI.h"
#include "misResultCode.h"
#include "misImageViewingItemsStruct.h"
#include "misStrctPatientData.h"
#include "BusinessEntities\point.h"

class misImageDataProperties;
class misImageIOProperties;
struct misImageViewingItemsStruct;
class misApplicationSetting;


class  misImage : public IImage
{
public:

	misImage();
	~misImage();

	virtual std::string GetUID() const;
	virtual void SetUID(const std::string& id);
	virtual void	DeepCopy(std::shared_ptr<IImage> image);
	virtual void Update() override;
	void SetName(std::string name);
	std::string GetName();
	misROI	GetROI();
	misROI	GetWorldDiemension();
	vtkTransform*  GetConfirmedDirectionTransform(void);
	std::vector<double>   GetScalerRangeNeeded(void);
	misImageDataModality GetImageModality(void) const override;
	void SetPrimeryUID(misUID uid);
	misUID GetPrimeryUID();
	
	// TODO: uncompleted
	misResultCode::ResultIds SetImageProperties(misImageDataProperties*  imageProperties);
	// all Image properties
	misImageDataProperties*  GetImageDataProperties(void);
	misResultCode::ResultIds SetResterictedPatientProperties(misPatientProperties  patientProperties);
	//  use for saving image properties in Data Layer
	misImageIOProperties	GetImageIOProperties(void);
	misImageViewingItemsStruct GetViewingStrct(void);
	MisObjectType	GetObjectType();

	// use for viewing in the GUI
	misDicomDataViewingProperties GetSimplifiedProperties(void);

	void ResetConfirmedTransform(void);

	// Some time image instead of axial is coronal or sagittal, or even mirrored. correctionMatrix corrects the image
	void SetConfirmedDirectionTransform(vtkMatrix4x4* correctionMatrix);
	bool SetROI(const misROI &roi);
	void DeepCopyOnlyImagePropeties(std::shared_ptr<IImage> image);
	void SetDuplicatedRangeActivation(bool val);
	void SetViewingProperties(misImageViewingType viewingType, misWindowLevelStr winlevStr);
	void SetSkinThreashold(double threshold);
	void SetBoneThreshold(double threshold);
	void SetTeethThreshold(double threshold);
	boost::optional<double> GetCurrentSkinThreshold(void) override;
	boost::optional<double> GetDeafaultSkinThreshold(void) override;
	boost::optional<double> GetCurrentBoneThreshold();
	boost::optional<double> GetCurrentTeethThreshold();
	parcast::PointD3 GetImageCenter() override;
	bool GetDuplicatedRangeActivation(void);
	bool CheckPrimaryConditionOnImageGeometry();
	std::string GetBinaryFileName() const;
	void SetBinaryFileName(std::string val);
	int* GetDimensions();
	void* GetScalarPointer();
	int GetScalarType();
	double* GetSpacing();
	void Modified();
	vtkSmartPointer<vtkImageData> GetRawImageData() const;
	void SetRawImageData(vtkSmartPointer<vtkImageData> val);
	void SetExternalSpacing(tgt::vec3 spacing);
	bool GetModificationFlag() const { return m_ModificationFlag; }
	void SetModificationFlag(bool val) { m_ModificationFlag = val; }
	bool GetModificationFlagBinariesPart() const { return m_ModificationFlagBinariesPart; }
	void SetModificationFlagBinariesPart(bool val) { m_ModificationFlagBinariesPart = val; }
	bool GetConfirmedDirection() const { return m_ConfirmedDirection; }
	void SetConfirmedDirection(bool val) { m_ConfirmedDirection = val; }
	misUID GetParentImageUID() const;
	void SetParentImageUID(misUID val);
	bool GetViewingNameCompletenessStatus() const { return m_ViewingNameCompletenessStatus; }
	void SetViewingNameCompletenessStatus(bool val) { m_ViewingNameCompletenessStatus = val; }
 
protected:

	MisObjectType                   m_ObjectType;
	std::string m_DataObjectUID;

private:

	misImageViewingItemsStruct      m_viewingStr;
	misImageDataProperties*		    m_ImageDataProperties;
	vtkTransform*               	m_ConfirmedCorrectionTransform;
	misROI							m_Roi;
	misApplicationSetting*          m_AppSetting;
	misPatientProperties			m_PatientProperties;

	void    FillInternalProperties(void);
	void    UpdateImageViewingProperties(void);

	// Default window level structure is an initial range (a window on the image histogram) for display 2d images with a
	// suitable contrast. The below functions calculate the center and the width of that window for CT and MR images.
	// The window parameters can be assumed to be constant for all CT images but for MR images the window parameters are
	// calculated based on the average and the standard deviation of the intensity of the image pixels.

	void UpdateCtDefaultWindowLevel();
	void UpdateMriDefaultWindowLevel();
	void UpdateSpectDefaultWindowLevel();

	void    UpdateImageRange(void);
	virtual	void  CallModificationObserver(void) {};

	//NOTE: this method just call by misDICOMImageloader to set the result of misSerieCheck validation which is calculated spacing 
	// based on position of slices.
	std::string  m_BinaryFileName;
	void CropImage(const misROI &roi);
	double	m_ActiveDuplicatedRange;
	void    DuplicateScalerRange(double* scalerRange);
	void    UpdateNumberOfImages(void);
	void    SetConfirmedDirectionTransform(vtkTransform* directionTransform);

	vtkSmartPointer<vtkImageData>  m_RawImageData;
	std::string m_Name;
	misUID m_PrimeryUID;
	bool m_ModificationFlag;
	bool m_ModificationFlagBinariesPart;
	bool m_ConfirmedDirection;
	misUID m_ParentImageUID;
	bool m_ViewingNameCompletenessStatus;
};