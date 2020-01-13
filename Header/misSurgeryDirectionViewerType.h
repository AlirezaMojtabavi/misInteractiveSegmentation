#pragma once

#include "VisualizationGeneralTypes.h"
#include "misSurgeryType.h"
#include "misViewerTypeDirection.h"

struct misSurgeryDirectionViewerType
{
	misSurgeryDirectionViewerType(){}
	misSurgeryDirectionViewerType(misSurgeryType sType, IMAGEORIENTATION orient, misViewerTypeDirection typeDir)
		:surgeryType(sType), orientation(orient), viewerType(typeDir)
	{
	}
	misSurgeryType surgeryType = UnKnownSurgery;
	IMAGEORIENTATION orientation = UNKnownDirection;
	misViewerTypeDirection viewerType = UnSetDirection;
};