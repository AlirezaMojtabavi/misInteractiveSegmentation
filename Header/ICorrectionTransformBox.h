#pragma  once
#include "misCoreEvents.h"

class  misROI;

// ComputeNormals create a box poly data for rendering textured plan and for managing interactions for correcting a transform
// by rotating a coefficient of 90 transforms
class ICorrectionTransformBox
{
public:
 
	virtual void On() = 0;
	virtual void Off() = 0;
	virtual int  GetLastSelectedFaceID() = 0;
	virtual void Reset() = 0;
	virtual void UpdateFacesTexture() = 0;
	virtual void UseDefaultFacesInformation() = 0;
	virtual int GetDefalutCellID(misTextureEnum textureName) = 0;
	virtual void InitilizeTransformCorrectionBox(vtkRenderWindowInteractor* interactor, 
		vtkProp3D* VolumeRep, const misROI& roi) = 0;
	virtual void AddActorToBoxWidget( vtkRenderWindowInteractor* interactor, 
		vtkProp3D* VolumeRep, const misROI& roi) = 0;
	virtual void UpdateOrientationCorrectionBox(vtkProp3D* VolumeRep, misROI roi ) = 0;
	virtual void UpdateBoxWidgetFacesInformation( misFaceInformation newFaceInformation ) = 0;
	virtual void ResetTexture() = 0;
	virtual misFaceInformation GetFaceInformation1st() const = 0;
	virtual misFaceInformation GetFaceInformation2nd() const = 0;
	virtual void UpdateFaceSelection( misTextureEnum appliedTexture ) = 0;
	virtual vtkSmartPointer<vtkMatrix4x4> CalculatePrimeryMatrix() = 0;
	virtual vtkSmartPointer<vtkMatrix4x4> CalculatedSecondryMatrix() = 0;
	virtual bool GetSecondFaceIsSelected() const = 0;
	virtual faceInformationListTypdef GetFacesInformationApplied() const = 0;
	virtual bool CheckNewFaceSelectedValidity() = 0;
	virtual void SetAppliedFaceInformation(faceInformationListTypdef facesInformationApplied) = 0;
	virtual void  SetBounding(double  bounds[6]) = 0;
	virtual void SetInteractor(vtkRenderWindowInteractor* interactor) = 0;
	virtual vtkSmartPointer<vtkRenderWindowInteractor> GetInteractor() const = 0;
	virtual void SetVolume( vtkProp3D * volume ) = 0;
};