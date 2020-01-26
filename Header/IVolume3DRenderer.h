#pragma once
#include "IVolumeRenderer.h"
#include "misROIWidget.h"
#include "TransferFuncs3D.h"
#include "IMedicalCameraDirection.h"
#include "ILandmarkPointerRepresentation.h"


enum class DentalSurgeryType;

class IVolume3DRenderer : public virtual IVolumeRenderer
{
public:

	typedef std::vector < std::shared_ptr < ILandmarkPointerRepresentation >> LandmarkListType;

	// Return a list contains all representation by provided name
	virtual std::vector<std::shared_ptr<IRepresentation>> FindRepresentationByName(const std::string& name) = 0;

	// Sets the Region of Interest
	virtual void SetROI(const double* data) = 0;


	virtual vtkProp3D* GetWidgetBoundedActor() = 0;
	// Adds the representation to the list of contained representations with special treatment in case of a voreen volume 
	// representation. It also adds the man model representation centered on the position of the representation if not already
	// present.

	// Add a model that displays patient orientation (Right hand is raised) and is synchronized with patient image and volume. 
	virtual void AddImageOrientation3DModel(std::shared_ptr<IRepresentation> pRepresentation) = 0;


	virtual void SetCurrentPosition(vtkMatrix4x4* info) = 0;

	// These methods are related to the viewer in volume viewer mode (one of the modes it can have at one time)
	virtual void SetVolume(misOpenglTexture* pTexture, std::shared_ptr<TransFuncIntensity> transferFunction) = 0;
	virtual void SetVolume(misOpenglTexture* imageTexture, ImageContainedTransferFuncs3D ImgCntTfs) = 0;
	virtual void PassVolumeMapToRepresentation() = 0;

	// The following methods perform the same action on the contained volume representation if the main representation is a volume.
	virtual void ReleaseImageResource() = 0;

	virtual void ClippingOn() = 0;
	virtual void ClippingOff() = 0;
	virtual void ClipingWidgetOn() = 0;
	virtual void ClippingWidgetOff() = 0;
	virtual void SetClippingPlane(tgt::vec4 plane) = 0;
	virtual void ZoomIn() = 0;
	virtual void ZoomOut() = 0;
	virtual void ResetZoom() = 0;

	virtual void InitializeCornerProperties() = 0;
	virtual misROIWidget* GetROIBox() = 0;
	virtual double * GetROICompressData() = 0;
	virtual void RemoveRenderingVolume() = 0;
	virtual void ModifyVolume() = 0;
	virtual void CompileVolumeShader() = 0;
	virtual void RemoveSegmentedVolume() = 0;
	virtual void OffAllScrews() = 0;
	virtual void OnAllScrews() = 0;
	virtual void SetAllScrewsLocked(bool isLocked) = 0;
	virtual void LockAllScrews() = 0;
	virtual void UnlockAllScrews() = 0;
	virtual std::map<misOpenglTexture*, ImageContainedTransferFuncs3D> GetVolumeMap() const = 0;
	virtual std::shared_ptr<IMedicalCameraDirection> GetMedicalCameraDirection()const = 0;
};

