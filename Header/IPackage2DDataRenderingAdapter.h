#pragma once
#pragma once

#include "IPackageDataRenderingAdapter.h"
#include "IVolumeSlicer.h"
#include "misStrctDataSets.h"
#include "IOblqueView.h"

class misVolumeSlicer;

enum IMAGEORIENTATION;
enum LANDMARKLABLETYPE;
enum misLandmarkType;

class IPackage2DDataRenderingAdapter :public virtual IPackageDataRenderingAdapter , public IOblqueView
{
public:
	virtual misWindowLevelStr GetCurrentWindowLevel(std::string imageUID) = 0;
	virtual void ApplyWindowlevel(std::string imageUID, misWindowLevelStr winLevStr) = 0;
	virtual void SetOpacityValueToTexture(std::string imageUID, float val) = 0;
	virtual void SetVisibilityValueToTexture(misUID imageUID, bool val) = 0;
	virtual void SetOrientation(IMAGEORIENTATION newOrientation) = 0;
	virtual void SetColorValueToTexture(misUID imageUID, misDoubleColorStruct Color) = 0;
	virtual void UpdateImageAnnotation(void) = 0;
	virtual void AddInternalObservers(itk::Command* ContrastObserver, itk::Command* backToMapObserver,
		itk::Command* stateObsrever) = 0;
	virtual void SetRealTimeMode(bool val) = 0;
	virtual void ResetMeasurment() = 0;
	virtual void UpdateSliderInGUI() = 0;
	virtual bool ShowImages(std::shared_ptr<ISimpleDataPackage> newPackage, const misVisualizationSetting& visualSetting,
		double minOpacity, bool resetZoom, misCursorType pWidgetType, std::shared_ptr<IImage>& mainImage) = 0;
	virtual std::shared_ptr<IVolumeSlicer> GetSlicer() = 0;

};
