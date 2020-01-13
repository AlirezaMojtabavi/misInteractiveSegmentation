#pragma once

#include "misobjectProperitiesEnums.h"
#include "misColorStruct.h"
#include "misVolumeViewingTypes.h"

struct misObjectProperties
{
	misObjectSizeType        ObjectSizeType;
	misColorStruct           ObjectColor;
	mis3DModelTypes          ObjectType;
	mis3DModelRenderingType  ObjectRenderingType;
	misVolumeViewingTypes    ObjectVolumeViewing;
	bool                     AutomaticExtractObjectBorder;

	void Reset()
	{
		ObjectSizeType = UnSetObjectSizeType;
		ObjectColor.Reset();
		ObjectType = UnSetModelType;
		ObjectRenderingType = UnSetRenderingType;
		ObjectVolumeViewing = misVolumeViewingTypes::UnsetViewingType;
		AutomaticExtractObjectBorder = false;
	};

	misObjectProperties()
	{
		this->Reset();
	};
};