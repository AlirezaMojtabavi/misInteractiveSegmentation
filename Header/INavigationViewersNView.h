#pragma once


#include "IPlanningGroupViewer.h"
#include "ISimpleDataPackage.h"
#include "BusinessEntities\Point.h"
#include "itkEventObject.h"
#include "itkObject.h"
#include "misColorStruct.h"
#include "misDistributionStruct.h"
#include "misEnums.h"
#include "misGroupViewerSetting.h"
#include "voreen/misCroppingDirectionInVR.h"
#include "ToolVisulizationProp.h"
#include "IPackageDataRenderingAdapter.h"
#include "IVolumeSlicer.h"

class IVolume3DRenderer;
class IPackage2DDataRenderingAdapter;
class IPackage3DDataRenderingAdapter;

// Needed interface for navigation and other subsequences to display a package in multiple viewers.
class INavigationViewersNView : public virtual parcast::IPlanningGroupViewer, virtual public IPackageDataRenderingAdapter
{
public:
	class IObliqueChanged
	{
	public:
		virtual void Changed(bool oblique) = 0;
	};

	class IPlanSelectedInViewer
	{
	public:
		virtual void Selected(misUID planUid) = 0;
	};

	virtual ~INavigationViewersNView() = default;
	enum TypeOfViewer { D2VIEWER, D3VIEWER, ALLVIEWERS };

	virtual void ClearAnnotationDetailFromViewer() = 0;
	virtual void Freeze() = 0;
	virtual void Unfreeze() = 0;
	virtual void SetRealTimeMode(bool val) = 0;
	virtual void SetDentalSurgeryType(DentalSurgeryType surgeryType) = 0;
	virtual void SetCroppingDirection(misCroppingDirectionInVR croppingDirection, const double* center, bool isobliqe) = 0;
	virtual void Reset2DZoom() = 0;
	virtual void ClipVolumeWithObliquePlane(const double* planeNormal, const double* center) = 0;
	// Sets the relative weight of the line used in drawing the cursor widget at the center of each of the image viewers.
	virtual void SetWidgetLineWeight(double weight) = 0;
	virtual void ChangeWidgetType(misCursorType cursorType) = 0;
	virtual void SetObliqueChangedObserver(std::weak_ptr<IObliqueChanged> observer) = 0;
	virtual void SetPlanIsSelectedInViewerObserver(std::weak_ptr<IPlanSelectedInViewer> observer) = 0;
	virtual void UpdateViewingPropertiesTexture(bool DisplayErasedObjectStatus, misColorStruct ColorStr) = 0;
	virtual void Render() = 0;
	virtual void SetAnnotationDetailToViewer() = 0;
	virtual void ClippingOff() = 0;
	virtual void UpdateSliderInGUI() = 0;
	virtual int	GetCurrentZoomPercentage() = 0;
	virtual double GetCurrentZoomProportion() = 0;
	//updating landmarks label and position when changing screw widget
	virtual std::shared_ptr<IVolumeRenderer> GetViewerByType(misViewerTypeDirection type) const = 0;
	virtual std::vector<std::shared_ptr<I3DViewer>> GetAllViewers() const = 0;
	virtual void SetImagePlanePosition(const double pos[3]) = 0;
	virtual void ApplyWindowlevel(misUID imageUID, misWindowLevelStr winLevStr) = 0;
	virtual std::vector<std::shared_ptr<IVolumeSlicer>> Get2DViewers() = 0;
	virtual parcast::Point<double, 3> GetCurrentPosition(void) = 0;
	virtual misWindowLevelStr GetCurrentWindowLevel(misUID imageUID) = 0;
	virtual void SetColorValueToTexture(misUID imageUID, misColorStruct Color) = 0;
	virtual void SetImageColor(std::vector<misUID> UIDs, misColorStruct imageColor) = 0;
	virtual misColorStruct GetImageColor(std::vector<misUID> UIDs) = 0;
	virtual void SetOpacityValueToTexture(misUID imageUID, float val) = 0;
	// Return viewers that are not imageviewer!
	virtual std::vector<std::shared_ptr<IVolume3DRenderer>> Get3DViewers() = 0;
	virtual std::vector<std::shared_ptr<IVolumeRenderer>> GetAllLandMarkViewers() const = 0;
	virtual void UpdateViewerROI(misROI roi) = 0;
	virtual void ResetROI(misROI roi) = 0;
	virtual void ResetROI() = 0;
	virtual void UpdateViewerWithImage(std::shared_ptr<IImage> image) = 0;
	virtual std::shared_ptr<IPackage3DDataRenderingAdapter> GetVolumePackageViewer() = 0;

	using IPackageDataRenderingAdapter::UpdateRepresentationTransforms;
	virtual void UpdateRepresentationTransforms(std::shared_ptr<ISimpleDataPackage> package) = 0;
	// Used by containing subsequence to notify the group viewer to reread panoramic curve from the current package
	virtual std::shared_ptr<IGroupViewerSetting> GetGroupViewerSetting() = 0;
	virtual std::shared_ptr<IPanoramicCoordinatesConverter> GetPanoramicCoordinateConverter() const = 0;
	virtual void Add3dRepresentation(std::shared_ptr<misRepresentation> PSurfaceRep) = 0;
	virtual void Add2DViewer(std::shared_ptr<IPackage2DDataRenderingAdapter> viewer, std::shared_ptr<Iwindows> window) = 0;
	virtual void Add3DViewer(std::shared_ptr<IPackage3DDataRenderingAdapter> viewer, std::shared_ptr<Iwindows> window) = 0;
	virtual  void Remove3dRepresentation(std::shared_ptr<misRepresentation> PSurfaceRep) = 0;
	virtual void ResetCamera() = 0;
	virtual void ResetMeasurment() = 0;
	virtual void SetRoiWidgetActivation(const double* roi, bool activation) = 0;
	virtual void ChangeViewerToMultipleImages() = 0;
	virtual void ChangeViewerToSameImages() = 0;

	virtual void SetOrientation(IMAGEORIENTATION newOrientation) = 0;
	virtual void SetGroupViewerSetting(std::shared_ptr<IGroupViewerSetting> pSettingStr) = 0;
	virtual std::map<std::shared_ptr<IVolumeRenderer>, ToolVisulizationProp> GetRenderingToolExtension() const = 0;
	virtual bool HasObserver(const itk::EventObject & event) const = 0;
	virtual unsigned long AddObserver(const itk::EventObject & event, itk::Command *command) = 0;
	virtual void InvokeEvent(const itk::EventObject& event) = 0;
	virtual	void SetVisibilityValueToTexture(misUID imageUID, bool val) = 0;
	virtual void SetDefaultVisibilityMap(std::vector<std::map<misPlaneEnum, bool>> map) = 0;
	virtual std::vector<std::shared_ptr<IPackageDataRenderingAdapter>> GetAllPackageViewers() const = 0;
	typedef std::vector<std::map<misPlaneEnum, bool>> VisibiltyMap;
	virtual void ShowPackage(std::shared_ptr<ISimpleDataPackage> pPackage, bool resetZoom)  = 0;
	virtual void ShowPackageImages(std::shared_ptr<ISimpleDataPackage> pPackage, bool resetZoom) = 0;
	virtual void SetVisiblityOfColorMap(misPlaneEnum planeIndex, bool val) = 0;
	virtual void SetColorMapTransFuncID(misPlaneEnum planeIndex, std::shared_ptr<TransFuncIntensity> val) = 0;
	virtual void SetColorValueToTexture(misPlaneEnum planeIndex, misDoubleColorStruct colorVal) = 0;
	virtual void SetOpacityValueToTexture(misPlaneEnum planeIndex, float opacityValue) = 0;
	virtual void ClearViewers() = 0;
	virtual std::vector<std::shared_ptr<Iwindows>> GetAllWindow() = 0;
	virtual void WarnFlyZone(const std::vector<std::vector<PropertiesOfPixelInImageStr>>& FlyZoneStatus) = 0;
	virtual void UpdatePlaneVisibilities(std::vector<std::map<misPlaneEnum, bool>> ) = 0;

 };
