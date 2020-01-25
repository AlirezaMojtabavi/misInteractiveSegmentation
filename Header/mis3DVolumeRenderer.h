#pragma once

#include "IVolume3DRenderer.h"
#include "I3DViewer.h"
#include "ICoordinateSystemRenderer.h"
#include "ILandmarkPointerRepresentation.h"
#include "IPanoramicCoordinatesConverter.h"
#include "IVolumeRayCaster.h"
#include "IWindows.h"
#include "misVolumeRendererContainer.h"
#include "misAnalysisStudioEvents.h"

#include "misCornerProperties.h"
#include "misManModelrepresentation.h"
#include "misMeasurment.h"
#include "misPlaneWidget.h"
#include "misROIWidget.h"
#include "ISettingsContainer.h"
#include "IUpdateLandmarkCameraView.h"
#include "IInitializeScrewWidget.h"
#include "misVolumeRenderer.h"
#include "misZoomFinder.h"
#include "IMedicalCameraDirection.h"
#include "IScrewViewer.h"
#include "LandmarkDataAndType.h"
#include "ILandmarkViewer.h"

class IScrewCompound;
class ICursorService;

// The mis3DVolumeRenderer class derives mis3DViewer and adds to it landmark management (adding, removing, ...), more specialized
// view (camera) settings, special treatment of 3d image (volume) representations, screw management (adding, removing, ...) as well
// as countless other features with uses still unknown to mankind.set
class mis3DVolumeRenderer : public virtual IVolume3DRenderer, public misVolumeRenderer
{
public:
	typedef std::vector<std::shared_ptr<ILandmarkPointerRepresentation>> LandmarkListType;
	using ScrewListType = std::vector<std::shared_ptr<IScrewCompound>>;

	mis3DVolumeRenderer(std::shared_ptr<ScrewListType> screwServiceList,
	                    std::shared_ptr<Iwindows> pWindow,
	                    int index,
	                    std::shared_ptr<I3DViewer> viewer,
	                    std::shared_ptr<ICornerProperties>,
	                    std::shared_ptr<IInitializeScrewWidget>,
	                    std::shared_ptr<IMedicalCameraDirection> medicalCameraDirection,
	                    std::shared_ptr<IVolumeRayCaster> volumeRenderer, misVolumeRendererContainer::Pointer dummy);
	~mis3DVolumeRenderer();
	void SetToolPosition(double xCoord, double yCoord, double zCoord) override; //double *GetBounds();
	void RemoveRepresentation(std::shared_ptr<IRepresentation> pRepresent);
	virtual void SetToolTransform(std::shared_ptr<ITransform> transform);
	void Reset() override;
	std::shared_ptr<ICursorService> GetCursorService() override;
	std::shared_ptr<IScrewCompound> GetScrewWidgetService(misUID uid) override;
	// Sets the Region of Interest
	virtual void SetROI(const double* data);
	virtual void SetROI(misROI data);
	// Initializes the underlying cursor service widget and adds an observer to its changed event.
	virtual void InitializeWidget(misCursorType widgetType, double pickingTolerance);
	virtual vtkProp3D* GetWidgetBoundedActor();
	// Adds the representation to the list of contained representations with special treatment in case of a voreen volume 
	// representation. It also adds the man model representation centered on the position of the representation if not already
	// present.
	void AddRepresentation(std::shared_ptr<IRepresentation> pRepresentation) override;
	std::vector<std::shared_ptr<IRepresentation>> FindRepresentationByName(const std::string& name) override;
	void AddCoordinateSytemRenderer(std::shared_ptr<ICoordinateSystemRenderer> coordianteRenderer) override;
	// Add a model that displays patient orientation (Right hand is raised) and is synchronized with patient image and volume. 
	void AddImageOrientation3DModel(std::shared_ptr<IRepresentation> pRepresentation);
	// Processes the received event and responds accordingly.
	virtual bool ProcessRequest(const itk::EventObject* event);
	void SetCurrentPosition(vtkMatrix4x4* info);
	// The following methods perform the same action on the contained volume representation if the main representation is a volume.
	virtual void ReleaseImageResource();
	void ClipingWidgetOn();
	void ClippingWidgetOff();

	std::shared_ptr<ICornerProperties> GetCornerProperties() const override;
	void InitializeCornerProperties() override;
	misROIWidget* GetROIBox();
	double* GetROICompressData();
	void ROIWidgetActivation(bool activation);
	void HighlightScrew(misUID screwUID, bool highlight) override;
	void OffAllScrews() override;
	void OnAllScrews() override;
	void SetAllScrewsLocked(bool isLocked) override;
	void RemoveAllScrewServices() override;
	void LockAllScrews() override;
	void UnlockAllScrews();
	void OnScrew(misUID screwUID) override;
	void OffScrew(misUID screwUID);
	void DeleteScrew(misUID screwUID);
	void DeleteAllScrews();
	void InitializeScrewWidget(misScrewWidgetData initVals, IMAGEORIENTATION orientation) override;
	vtkRenderer* GetRenderer() override;
	misViewerTypeDirection GetTypeDirection(void) const override;
	void SetShowManModel(bool val) override;
	virtual void SetPanoramicCoordinateConverter(
		std::shared_ptr<const IPanoramicCoordinatesConverter> coordinateConverter);
	virtual void SetDentalSpecialViewsEnable(bool enabled);
	std::map<misOpenglTexture*, ImageContainedTransferFuncs3D> GetVolumeMap() const;
	void RemoveSegmentedVolume() override;
	void SetMainRepresentation(std::shared_ptr<IRepresentation> pMainRep, IMAGEORIENTATION orientation) override;
	void UpdateWindowSize(misStrctWindowSize& size) override;
	std::shared_ptr<TransFuncIntensity> GetColormapTransferFunction() const;
	void SetColormapTransferFunction(std::shared_ptr<TransFuncIntensity> val);
	bool GetShowLabels() const;
	void SetShowLabels(bool val);
	void RemoveRepresentationByName(std::string name) override;
	std::shared_ptr<IRepresentation> GetMainRepresentation() override;

	std::shared_ptr<I3DViewer> Get3DViewer() const override;
	void Render() override;
	unsigned long AddObserver(const itk::EventObject& event, itk::Command* command) override;
	bool HasObserver(const itk::EventObject& event) const override;
	void InvokeEvent(const itk::EventObject& event) override;
	void SetVolume(misOpenglTexture* pTexture, std::shared_ptr<TransFuncIntensity> transferFunction) override;
	void SetVolume(misOpenglTexture* imageTexture, ImageContainedTransferFuncs3D ImgCntTfs) override;
	void PassVolumeMapToRepresentation() override;
	void ClippingOn() override;
	void ClippingOff() override;
	void SetClippingPlane(tgt::vec4 plane) override;
	void ModifyVolume() override;
	void CompileVolumeShader() override;
	void RemoveRenderingVolume() override;
	void SetDentalSurgeryType(DentalSurgeryType surgeryType) override;
	std::shared_ptr<Iwindows> GetWindow() const override;
	void SetState(int val) override;
	bool HasRepresentationByName(const std::string& name) override;
	void MakeCurrentRenderer() override;
	virtual IMAGEORIENTATION GetOrientationDirection();
	void SetViewPort(const misViewPort& val) override;
	void ZoomIn() override;
	void ZoomOut() override;
	void ResetZoom() override;
	std::shared_ptr<IMedicalCameraDirection> GetMedicalCameraDirection() const override;
	void SetObliqueFlag(bool isOblique) override;
protected:
	void SetROIActive();
	void SetROIInteractor();
	virtual void ROIClickAction(vtkObject* caller, unsigned long eventId, void* callData);
	virtual void UpdateWidgetBox(vtkObject* caller, unsigned long eventId, void* callData);
	DentalSurgeryType GetDentalSurgeryType();
	// Sets the main representation as a new volume representation and resets the volume list.
	void ResetVolume();
	// Calculates and gets the bounding box to be used for the 3D widget. It uses the image dimensions by extending image bounds
	// in each direction while keeping its centre fixed. This yields the widget bounds before the transform is applied to it.
	void GetWidgetBoundingBox(double bounds[6], double extensionScaleFactor = 1);
	bool IsDentalSpecialViewsEnabled() const;
	bool m_IsPointWidgetObserverAdded;
	bool m_IsPointSelectObserverAdded;
	std::shared_ptr<ICursorService> m_CursorService;
	vtkSmartPointer<misPlaneWidget> m_ClippingPlaneWidget;
	std::shared_ptr<ICornerProperties> m_Cornerproperties;
	using ScrewListType = std::vector<std::shared_ptr<IScrewCompound>>;
	std::shared_ptr<IRepresentation> m_MainRepresentation; // See SetMainRepresentation().
	virtual void SetTypeDirection(misViewerTypeDirection) override;

private:

	

	virtual void InteractionStyleCallback(vtkObject* caller, unsigned long eventId, void* callData);;
	virtual void WidgetChangeAction(vtkObject* caller, unsigned long eventId, void* callData);
	virtual void UpdateScrewWidget(vtkObject* caller, unsigned long eventId, void* callData);
	parcast::PointD3 GetLablePosition(const double* position, const itk::BoundingBox<double, 3, double>::Pointer
	                                  & boundingBox, const double handleLength, const double offsetAngle) const;
	void SetWindow(std::shared_ptr<Iwindows> pWindow, int index);


public:
	misVolumeRendererContainer::Pointer GetDummySubject() override;
 private:
	std::shared_ptr<misManModelrepresentation> m_ManModel;
	std::shared_ptr<IVolumeRayCaster> m_VolumeRnderer;
	bool m_ShowManModel;
	bool m_DentalSpecialViewEnable;
	std::shared_ptr<TransFuncIntensity> m_ColormapTransferFunction;
	bool m_ShowLabels;
	misVolumeRendererContainer::Pointer m_DummyObject ;
	DentalSurgeryType m_DentalSurgeryType;
	misZoomFinder m_ZoomFinder;
	unsigned int m_CurrentZoomPercentage = 100;
	std::shared_ptr<IMedicalCameraDirection> m_MedicalCameraDirection;
	std::shared_ptr<parcast::IScrewViewer> m_ScrewViewer;
	bool m_IsOblique = false;
	misViewerTypeDirection m_ViewerTypeDirection;
	// Inherited via IVolume3DRenderer
};
