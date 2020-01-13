#pragma once
#include "misStrctDataSets.h"
#include "misWindowLevelStr.h"
#include "I2DRepresentation.h"

// The  I2DImageRenderingAdapter class get images and convert images to rendering component on graphic card 
class I2DImageRenderingAdapter
{
public:
	virtual ~I2DImageRenderingAdapter() = default;
	virtual void ShowImages(std::shared_ptr<IImage> firstImage , bool , std::shared_ptr<IImage> secondImage , bool , double minOpacity) = 0;
	virtual void Reset() = 0;
	virtual void SetImage(std::shared_ptr<IImage> pImage, double minOpacity) = 0;
	virtual void SetImage(misLayerEnum layerIndex, std::shared_ptr<IImage> pImage, double minOpacity) = 0;
	virtual void SetNextImage(misPlaneEnum planeIndex, misLayerEnum layerIndex, std::shared_ptr<IImage> pImage, double minOpacity) = 0;
	virtual void SetNextImage(misPlaneEnum planeIndex, std::shared_ptr<IImage> pImage, double minOpacity) = 0;
	virtual misWindowLevelStr GetCurrentWindowLevel(misUID imageUID) = 0;
	virtual misPlaneEnum GetCorrespondingPlaneIndex(misUID ParentImageUID) const= 0;
	virtual void SetWidgetType(misCursorType val) = 0;
};
