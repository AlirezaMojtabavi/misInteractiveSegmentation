#pragma once
#include "IImage.h"
#include "misEnums.h"

class IVolumeViewerInitilizer
{
public:
	virtual void Initialize(std::shared_ptr<IImage> tempImage) = 0;
	virtual void SetWidgetType(misCursorType val) = 0;
	virtual ~IVolumeViewerInitilizer() = default;
};
