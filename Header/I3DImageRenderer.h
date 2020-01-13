#pragma once
#include "misStrctDataSets.h"
#include "misWindowLevelStr.h"
#include "I2DRepresentation.h"
class IImage;
// The  I3DImageRenderer class get images and convert images to rendering component on graphic card 
class I3DImageRenderer
{
public:
	virtual void ShowImages(ImageDependencyListTypes newImageDataDependencies) = 0;
	virtual void Reset() = 0;
	virtual void SetImage(std::shared_ptr<IImage> pImage) = 0;
	virtual void SetWidgetType(misCursorType val) = 0;
};
