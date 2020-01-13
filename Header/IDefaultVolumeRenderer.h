#pragma once
#include "misStrctDataSets.h"
#include "misobjectProperitiesEnums.h"
#include "misVolumeViewingTypes.h"


class IDefaultVolumeRenderer
{
public:
	virtual void ShowDefaultVolume(int SegmentedNum, ImageDependencyListTypes currentImageDataDependencies,
		misVolumeViewingTypes volumeViewing) = 0;
	virtual void SetWidgetType(misCursorType pWidgetType) = 0;
	virtual void SetSceneReferenceUID(const std::string& sceneReferenceUID) = 0;
	virtual ~IDefaultVolumeRenderer() = default;

};