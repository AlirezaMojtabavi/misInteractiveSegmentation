#pragma once

#include "misColorStruct.h"
#include "voreen/misCroppingDirectionInVR.h"
#include "misPlannedNavigationStageSettings.h"
#include "misTimePassingForActionPropertiesStr.h"
#include "serializable.h"

class misNavigationSetting:public Serializable
{
	misPrivateVariableWithPublicAccessorsMacro(misPlannedNavigationStageSettings, m_PlannedNavigationStageSettings, PlannedNavigationStageSettings);

public:
	bool           ShowLandmarkError;
	bool           attachCameraToTool;
	bool		   VolumeObliqueCropping;
	misColorStruct secondImageColor;
	bool           AutomaticFindPackageOnSelected;
	double         TimeForAutoDisappearToolMarkerWindow; // -1 mean do not automatic disappear
	double		   FinalOpacityForAutoDisappearToolMarkerWindow; // 0 to 1
	std::vector<int> m_VirtualTipLengthList;

	misTimePassingForActionPropertiesStr AutomaticFullScreen;
	misToolFixationPropertiesStr         ToolFixationForTakingSnapshot;
	misCroppingDirectionInVR             CroppingDirection;

	void serialize( XmlSerializer& s ) const;
	void deserialize( XmlDeserializer& s );
};