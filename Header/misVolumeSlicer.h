#pragma once

#include "IVolumeSlicer.h"
#include "misCameraInteraction.h"
#include "misEnums.h"
#include "misEvent.h"
#include "misImageContrastObserver.h"
#include "misMacros.h"
#include "misSideAnnotation.h"
#include "misImageAnnotation.h"
#include "I3DViewer.h"
#include "IDentalQuadrantFinder.h"
#include "misImageViewerAnnotations.h"
#include "ILandmarkVisibilty.h"
#include "IVolume3DRenderer.h"
#include "IInitializeScrewWidget.h"
#include "IUpdateLandmarkCameraView.h"
#include "misVolumeRendererContainer.h"
#include "misManModelrepresentation.h"
#include <ISettingsContainer.h>
#include "IVolumeSlicer.h"
#include "BiopsyNavigationUiUpdater.h"
#include "misevent.h"
#include "misSimplePointType.h"
#include "IScrewViewer.h"
#include "misVolumeRenderer.h"
#include "IBackToPanMode.h"
#include "SlicerPointSelectAction.h"
#include "LandmarkDataAndType.h"
#include <IPilotIndicatorColorSpecifier.h>
#include <vtkCaptionActor2D.h>
#include "IPanImage.h"
#include "TypeDirection.h"
#include "ILandmarkViewer.h"



#pragma warning (push)
#pragma warning (disable : 4800)	// IGSTK crap


#pragma warning (pop)

// The misVolumeSlicer class is a specialized type of mis3DVolumeRenderer with modified behavior for displaying 2D sections of a
// 3D image. Landmark management and other parent class features are also available to misVolumeSlicer.
class misVolumeSlicer : public virtual IVolumeSlicer, public misVolumeRenderer
{
public:
	typedef std::vector<std::shared_ptr<ILandmarkPointerRepresentation>> LandmarkListType;
	using ScrewListType = std::vector<std::shared_ptr<IScrewCompound>>;
	misVolumeSlicer(std::shared_ptr<ScrewListType> screws, std::shared_ptr<Iwindows> pWindow
	                , int index,
	                std::shared_ptr<I3DViewer> viewer,
	                std::shared_ptr<ICornerProperties>,
	                std::shared_ptr<IInitializeScrewWidget>, vtkSmartPointer<misInteractorSTyleImageExtend>,
	                misMeasurment::Pointer, misVolumeRendererContainer::Pointer,
	                std::shared_ptr<ICursorService>, std::shared_ptr<IBackToPanMode> backToPanMOde,
	                double differenceForViewingSeed, std::shared_ptr<misCameraInteraction> cameraInteraction);
	~misVolumeSlicer();

	void ShowAnnotationDetailOn() override;
	void ShowAnnotationDetailOff() override;
	void SetShowAnnotationDetail(bool status) override;
	bool ShowAnnotationDetail() const override;
	// Calls superclass Render() after updating camera, screw view, landmark view, region of interest. It also renders the video
	// texture if the GPU representation is a video GPU representation.
	void Render() override;
	// Reset image viewer zoom level to its default value and propagates the change to observer(s) - GUI.
	void ResetZoom() override;
	// Remove images and volumes representation from viewer
	virtual void ReleaseImageResource() override;
	void AddRepresentation(std::shared_ptr<IRepresentation> pRepresentation) override;
	virtual bool ProcessRequest(const itk::EventObject* event) override;
	//update  landmark position at index 
	void InitializeWidget(misCursorType widgetType,  double pickingTolerance) override;
	virtual void SetROI(const double* radius);
	virtual void SetROI(const misROI& data);
	virtual void InitializeCornerProperties() final;
	void SetToolPosition(double xCoord, double yCoord, double zCoord);
	bool HasRepresentationByName(const std::string& name);
	std::vector<std::shared_ptr<IRepresentation>> FindRepresentationByName(const std::string& name);
	void SetToolTransform(std::shared_ptr<ITransform> transform);
	void AddCoordinateSytemRenderer(std::shared_ptr<ICoordinateSystemRenderer> coordianteRenderer);
	void UpdateImage(bool FocalPointIsPlaneCenter = true) override;
	virtual void SetControlToPan() override;
	void GetWidgetFocalPoint(double [3]) override;
	bool ChangeMeasurmentMode(MEASURMENTMODE measurmentMode) override;
	void ResetGeneralToolbarState() override;
	void SetGeneralToolbarState(const misGeneralToolbarState& generalToolbarState) override;
	misGeneralToolbarState GetGeneralToolbarState() const override;
 	std::shared_ptr<misCameraInteraction> GetCameraService() override;
	 std::shared_ptr<parcast::WindowLevelSetting> GetWindowLevel() const override;

	void SetViewingProperties(misPlaneEnum planeIndex, misWindowLevelStr winLevStr) override;
	void SetObliqueFlag(bool isOblique) final;
	void SetOrientationDirection(IMAGEORIENTATION newOrientation) override;
	// Return image viewer orientation based on added representation orientation
	void ApplyOffset(double offset) override;
	void SetImageSliceViewerZoomFactor(double zoomFactor) override;
	virtual misMeasurment* GetMeasurmentService() override;
	// Change interaction style like pan, zoom, change contrast,..
	virtual void SetInteractionMode(INTERACTIONMODE mode) override;
	virtual void ResetContrast() override;
	virtual InteractionState GetInteractionState() const override;
	virtual void SetInteractionState(InteractionState val) override;
	virtual void ResetViewer() override;
	void SetAnnotationEnabled(bool showEnable);
	void SetProstrateState(bool prostrator);
	void SetSurgeryType(misApplicationType surgeryType);
	misGeneralToolbarState ApplyMeasurment(misGeneralToolbarState ls);
	void UpdatePanMode();
	void CheckFlyZone(const std::string& segmentationRegion) override;
	void UpdateWindowSize(misStrctWindowSize& size) override;
	void CreateImageAnnotation(void) override;
	// Gets the number of representation objects contained within this viewer.
	int GetNumberOfRepresentations() override;
	std::shared_ptr<I2DRepresetation> GetImageRprensentaion() final;
	void SetRealTimeMode(bool val) final;
	bool GetRealTimeMode() const override;
	virtual std::shared_ptr<ICornerProperties> GetCornerProperties() const override;
	void LockAllScrews();
	void UnlockAllScrews();
	void SetAllScrewsLocked(bool isLocked);
	void RemoveAllScrewServices();
	vtkRenderer* GetRenderer();
	std::shared_ptr<IRepresentation> GetMainRepresentation();
	std::shared_ptr<ICursorService> GetCursorService();
	void OnScrew(misUID screwUID);
	unsigned long AddObserver(const itk::EventObject& event, itk::Command* command);
	void InvokeEvent(const itk::EventObject& event);
	bool HasObserver(const itk::EventObject& event) const;
	void RemoveRepresentation(std::shared_ptr<IRepresentation> pRepresent);
	void AddImageOrientation3DModel(std::shared_ptr<IRepresentation> pRepresentation);
	void DeleteAllScrews();
	std::shared_ptr<I3DViewer> Get3DViewer() const;
	std::shared_ptr<IScrewCompound> GetScrewWidgetService(misUID uid) override;

	std::shared_ptr<Iwindows> GetWindow() const override; // Gets the render window = 0.
	double* GetROICompressData() override;
	void SetMainRepresentation(std::shared_ptr<IRepresentation> pMainRep, IMAGEORIENTATION orientation) override;
	void Reset() override;

	void RemoveRepresentationByName(std::string name) override;
	void MakeCurrentRenderer() override;
	void SetViewPort(const misViewPort& val) override;
	void SetShowManModel(bool val) override;
	void SetDentalSurgeryType(DentalSurgeryType surgeryType) override;
	void DeleteScrew(misUID screwUID) override;
	void HighlightScrew(misUID screwUID, bool highlight) override;
	void SetROI(misROI data) override;
	void ROIWidgetActivation(bool activation) override;
	void SetDentalSpecialViewsEnable(bool enabled) override;
	void SetPanoramicCoordinateConverter(std::shared_ptr<const IPanoramicCoordinatesConverter> coordinateConverter)
	override;

	void InitializeScrewWidget(misScrewWidgetData initVals, IMAGEORIENTATION orientation) override;

	void OffScrew(misUID screwUID) override;
	void SetState(int val) override;
 
 private:
	virtual void UpdateWidgetBox(vtkObject* caller, unsigned long eventId, void* callData);
	virtual void InteractionStyleCallback(vtkObject* caller, unsigned long eventId, void* callData);
	virtual void ROIClickAction(vtkObject* caller, unsigned long eventId, void* callData);
	virtual void WidgetChangeAction(vtkObject* caller, unsigned long eventId, void* callData);
	DentalSurgeryType GetDentalSurgeryType();
	bool IsDentalSpecialViewsEnabled() const;
	virtual void UpdateScrewWidget(vtkObject* caller, unsigned long eventId, void* callData);
	void UpdateViewROIBox();
	virtual void SetImageStyle() override;
	void FindProperDirection(double [3], double [3]);
 	void SetInteractionStyleProperties();
	void SetImageContrast(misPlaneEnum planeIndex);
	void UpdateDentalSideAnnotationsBuilder();
	virtual void SetDefaultWindowLevel() override;
	void SetWidgetFocalPoint(const double*);
	void UpdateLandmarkPosition();
	void CaptureLandmark(double* position);
	virtual vtkProp3D* GetWidgetBoundedActor();
	void SetROIActive();
	void SetROIInteractor();
	void ModifyPlane(misPlanWidget* planWidget, misScrewWidgetData &screwWidgetVal);
	std::shared_ptr<misCameraInteraction> m_CameraService;
	vtkSmartPointer<misInteractorSTyleImageExtend> m_pImageStyle;

	bool m_IsOblique;
	double m_WidgetFocalPoint[3];
	bool m_RealTimeMode;
	std::shared_ptr<misImageAnnotation> m_ImageAnnotations;
	std::shared_ptr<misSideAnnotation> m_SideAnnotations;
	vtkSmartPointer<misImageContrastObserver> m_ImageContrastObserver = vtkSmartPointer<misImageContrastObserver>::New();
	misMeasurment::Pointer m_MeasurmentService;
	misGeneralToolbarState m_GeneralToolbarState;
	bool m_ShowAnnotation;
	bool m_ProstrateState;
	misApplicationType m_SurgeryType;
	std::shared_ptr<parcast::IDentalViewSideAnnotationTextBuilder> m_DentalAnnotationBuilder;
	std::shared_ptr<parcast::IDentalQuadrantFinder> m_QuadrantFinder;
	misImageViewerAnnotations m_AnnotationUpdater;
	bool m_ShowAnnotationDetail = false;
	std::shared_ptr<IRepresentation> m_MainRepresentation = nullptr; // See SetMainRepresentation().
	std::shared_ptr<ICornerProperties> m_Cornerproperties;
	std::shared_ptr<ICursorService> m_CursorService;
	void GetWidgetBoundingBox(double bounds[6], double extensionScaleFactor = 1);
	void SetWindow(std::shared_ptr<Iwindows> pWindow, int index);
	virtual void SetTypeDirection(misViewerTypeDirection) override;

public:
	misViewerTypeDirection GetTypeDirection() const override;
	IMAGEORIENTATION GetOrientationDirection() const override;
	misVolumeRendererContainer::Pointer GetDummySubject() override;
private:
	bool m_IsPointWidgetObserverAdded = false;
	misVolumeRendererContainer::Pointer m_DummyObject;
	bool m_ShowManModel;
	std::shared_ptr<misManModelrepresentation> m_ManModel;
	DentalSurgeryType m_DentalSurgeryType = DentalSurgeryType::MAXILLA;
	bool m_DentalSpecialViewEnable = false;
	std::shared_ptr<parcast::IScrewViewer> m_ScrewViewer;
	std::shared_ptr<IBackToPanMode> m_BackToPanMode;
	std::shared_ptr<parcast::WindowLevelSetting>  m_WindowLevelSetting = std::make_shared<parcast::WindowLevelSetting>();
	std::shared_ptr<IPanImage> m_PanImage;
	misViewerTypeDirection m_ViewerTypeDirection;
	// Inherited via IVolumeSlicer
};

 
