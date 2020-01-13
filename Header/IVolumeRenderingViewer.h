#pragma once
#include "IWindows.h"
#include "misROI.h"

class TransFuncIntensity;
class misOpenglTexture;
class IvolumeRepresentation;
class misVolumePointPicker;
class IVolumeRayCaster
{
public:
	virtual ~IVolumeRayCaster()
	{}
	virtual void PassVolumeMapToRepresentation() = 0;
	virtual void UpdateWindowSize(misStrctWindowSize &size) = 0;
	virtual void SetROI(misROI data) = 0;
	virtual void UpdateRaycastingTexture() = 0;
	virtual void UpdatePointPicker(vtkPicker* picker) = 0;

	virtual void SetToolPosition(double xCoord, double yCoord, double zCoord) = 0;	
	virtual void ClippingOn() = 0;
	virtual void ClippingOff() = 0;
	virtual void SetClippingPlane(tgt::vec4 plane) = 0;
	virtual void Render() = 0;
	virtual void SetVolume(misOpenglTexture* pTexture, std::shared_ptr<TransFuncIntensity> transferFunction) = 0;
	virtual void SetVolume(misOpenglTexture* imageTexture, ImageContainedTransferFuncs3D ImgCntTfs) = 0;
	virtual void ModifyVolume() = 0;
	virtual void CompileVolumeShader() = 0;
	virtual std::shared_ptr<IvolumeRepresentation> GetRepresentation() const = 0;
	virtual void SetRepresentation(std::shared_ptr<IvolumeRepresentation>) = 0;

	virtual void RemoveVolumeWithId(misUID ID) = 0;
	virtual void RemoveSegmentedVolume() = 0;
	virtual void RemoveOldTexture(misOpenglTexture* oldTexture) = 0;
	virtual void RemoveRenderingVolume() = 0;
	virtual std::map<misOpenglTexture *, ImageContainedTransferFuncs3D> GetVolumeMap() const  = 0;
	virtual void SetRenderer(vtkSmartPointer<vtkRenderer> val) = 0;
	virtual void Reset() = 0;
};