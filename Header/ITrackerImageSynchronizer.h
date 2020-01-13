#pragma once
#include "IPanoramicTransformConverter.h"
#include "IVolume3DRenderer.h"
#include "ITrackingTool.h"
#include "ToolVisulizationProp.h"
#include "IVirtualTipSynchronizer.h"


// Synchronize scene with navigation tools
class ITrackerImageSynchronizer : public IVirtualTipSynchronizer
{
public:

	virtual void SetToolPosition(double* center) = 0;
	virtual void AddTool(std::shared_ptr<ITrackingTool> toolData) = 0;
	virtual void SetRenderingToolSceneReference(std::string refernce) = 0;
	virtual void SetToolTransform(vtkMatrix4x4* toolTransform) = 0;
	virtual void ShowTorus(bool visibility) = 0;
	virtual void SetViewers(std::map<std::shared_ptr<IVolumeRenderer>, ToolVisulizationProp>  val) = 0;
	virtual void Freeze() = 0;
	virtual void SetPanoramicTransformConvertor(std::shared_ptr<IPanoramicTransformConverter> val) = 0;
	virtual void SetPanoramicCoordinateConverter(std::shared_ptr<IPanoramicCoordinatesConverter> val) = 0 ;
	virtual void Unfreeze() = 0;
	virtual void AddExistingRepresentation() = 0;
	virtual void ClearViewers() = 0;
};
