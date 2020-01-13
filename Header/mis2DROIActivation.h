#pragma once
#include "BusinessEntities\Point.h"
#include "misROI.h"
#include <VisualizationGeneralTypes.h>


class mis2DROIActivation
{
public:
	mis2DROIActivation(misROI roi, IMAGEORIENTATION orientation);
	bool IsActive(parcast::Point<double, 3> position);
private:
	misROI m_ROI;
	IMAGEORIENTATION m_Orientation;
};

