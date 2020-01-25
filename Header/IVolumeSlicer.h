#pragma once

#include "misInteractorStyleImageExtend.h"
#include "misMeasurment.h"
#include "misPlaneContrast.h"
#include "ICornerProperties.h"
#include "I3DViewer.h"
#include <misLandmarkenums.h>
#include "IScrewCompound.h"
#include "ICursorService.h"
#include "misImageContrastObserver.h"
#include "IVolumeRenderer.h"
#include <../Adapters/IPilotIndicatorColorSpecifier.h>


// This class is an interface for 2D viewers Such as Panoramic view or each of the standard views.
// Date :  May 2016
// Author : MohsenRahimimoghaddam

class misCameraInteraction;
class misPlanarRepresentation;

class IVolumeSlicer :public virtual IVolumeRenderer
{
public:
	// set interaction mode to pan
	virtual void SetControlToPan() = 0;
	virtual void UpdatePanMode() = 0;

	//restart image contrast to the default value
	virtual void ResetContrast() = 0;

	// Change interaction style like pan, zoom, change contrast,..
	virtual void SetInteractionMode(INTERACTIONMODE mode) = 0;

	// Set interaction style of the viewer to image viewing
	virtual void SetImageStyle() = 0;

	// Set default window level 
	virtual void SetDefaultWindowLevel(void) = 0;

	// ??? 
	virtual misMeasurment* GetMeasurmentService() = 0;

	// Set interaction state for a viewing window (e.g. Pan, Contrast ...)
	virtual InteractionState GetInteractionState() const = 0;
	virtual void SetInteractionState(InteractionState val) = 0;
	virtual void SetGeneralToolbarState(const misGeneralToolbarState &generalToolbarState) = 0;
	virtual misGeneralToolbarState GetGeneralToolbarState() const = 0;
	virtual void ResetGeneralToolbarState() = 0;
	virtual void ResetViewer() = 0;
	virtual void UpdateImage(bool FocalPointIsPlaneCenter = true) = 0;
	virtual std::shared_ptr<I2DRepresetation> GetImageRprensentaion() = 0;
	virtual void ApplyOffset(double offset) = 0;
	virtual void CreateImageAnnotation(void) = 0;

	virtual void SetOrientationDirection(IMAGEORIENTATION newOrientation) = 0;
	virtual void SetImageSliceViewerZoomFactor(double zoomFactor) = 0;
	virtual void ResetZoom() = 0;
	virtual void GetWidgetFocalPoint(double[3]) = 0;
	virtual std::shared_ptr<misCameraInteraction> GetCameraService() = 0;
	virtual void SetViewingProperties(misPlaneEnum planeIndex, misWindowLevelStr winLevStr) = 0;
	virtual void SetRealTimeMode(bool val) = 0;
	virtual bool GetRealTimeMode() const = 0;
	virtual void CheckFlyZone(const std::string& segmentationRegion) = 0;
	virtual void LockAllScrews() = 0;
	virtual void OnScrew(misUID screwUID) = 0;
	virtual void ShowAnnotationDetailOn() = 0;
	virtual void ShowAnnotationDetailOff() = 0;
	virtual void SetShowAnnotationDetail(bool status) = 0;
	virtual bool ShowAnnotationDetail() const = 0;
	virtual int GetNumberOfRepresentations() = 0;
	virtual IMAGEORIENTATION GetOrientationDirection() const = 0;
	// Remove images and volumes representation from viewer
	virtual void ReleaseImageResource() = 0;
	virtual void AddImageOrientation3DModel(std::shared_ptr<IRepresentation> pRepresentation) = 0;
	virtual double * GetROICompressData() = 0;
	virtual std::shared_ptr<I3DViewer> Get3DViewer() const = 0;
	virtual bool ChangeMeasurmentMode(MEASURMENTMODE measurmentMode) = 0;
	virtual std::shared_ptr<parcast::WindowLevelSetting> GetWindowLevel() const = 0;
};
