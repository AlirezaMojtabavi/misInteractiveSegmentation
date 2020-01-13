#pragma once

#include "mis3DModelViewingProperties.h"
#include "misColorStruct.h"
#include "misTypes.h"
#include "misobjectProperitiesEnums.h"
#include "misVolumeViewingTypes.h"

// this class assigns a color and opacity to the specified range of the intensity threshold
struct misVolumeRangeColor
{
	std::string Name;
	misUID objectUID;
	bool AutomaticColorMode = true;
	misColorStruct	volumeColor;
	double minThreshold= -1;
	bool UsedDeafultThreshold = true;
	double maxThreshold = -1;
	bool	UsedDeafultMaxThreshold = true;
	mis3DModelObjectOpacityPropertiesStrct  visibilityProp;
 };
typedef std::map<misVolumeViewingTypes, misVolumeRangeColor>  misVolumeComponentPropTypdef;
typedef std::pair<misVolumeViewingTypes, misVolumeRangeColor>  misVolumeComponentPair;

