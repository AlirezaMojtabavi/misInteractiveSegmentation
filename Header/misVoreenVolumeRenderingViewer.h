#pragma once
#include "IVolumeRayCaster.h"
#include "misTransferFunctionSelecting.h"
#include "misVoreenRepresentation.h"

class misVoreenVolumeRenderingViewer :	public IVolumeRayCaster
{
public:

	misVoreenVolumeRenderingViewer(vtkSmartPointer<vtkRenderer> renderer);
	 void PassVolumeMapToRepresentation() override;
	 void UpdateWindowSize(misStrctWindowSize &size) override;
	 void SetROI(misROI data) override;
	 void UpdateRaycastingTexture() override;

	 void UpdatePointPicker(vtkPicker* picker) override;

	 void SetToolPosition(double xCoord, double yCoord, double zCoord) override;
	 void ClippingOn() override;
	 void ClippingOff() override;
	 void SetClippingPlane(tgt::vec4 plane) override;
	 void Render() override;
	 void SetVolume(misOpenglTexture* pTexture, std::shared_ptr<TransFuncIntensity> transferFunction) override;
	 void SetVolume(misOpenglTexture* imageTexture, ImageContainedTransferFuncs3D ImgCntTfs) override;
	 void ModifyVolume() override;
	 void CompileVolumeShader() override;
	 void RemoveVolumeWithId(misUID ID) override;
	 void RemoveSegmentedVolume() override;
	 void RemoveOldTexture(misOpenglTexture* oldTexture) override;
	 void RemoveRenderingVolume()override ;
	 std::map<misOpenglTexture *, ImageContainedTransferFuncs3D> GetVolumeMap() const  override;
	 void SetRenderer(vtkSmartPointer<vtkRenderer> val) override;
	 void Reset() override;
	 virtual std::shared_ptr<IvolumeRepresentation> GetRepresentation() const override;

	void SetRepresentation(std::shared_ptr<IvolumeRepresentation>) override;
private:


	std::shared_ptr<IvolumeRepresentation> m_VoreenRepresentation;
	double m_SampeRate = 0;
	vtkSmartPointer<vtkRenderer> m_Renderer;
	std::map<misOpenglTexture*, ImageContainedTransferFuncs3D> m_VolumeMap;
	misTransferFunctionSelecting* m_TransferFunctionSelect = nullptr;

};

