#include "stdafx.h"
#include "..\Header\mis2DROIActivation.h"
#include "VisualizationGeneralTypes.h"

mis2DROIActivation::mis2DROIActivation(misROI roi, IMAGEORIENTATION orientation)
	:m_ROI(roi), m_Orientation(orientation)
{
}

bool mis2DROIActivation::IsActive(parcast::Point<double, 3> CurrentPos)
{
	auto center = m_ROI.GetCenter();
	if (m_Orientation == AXIAL)
	{
		center[2] = CurrentPos[2];
		return m_ROI.ContainsPoint(center[0], center[1], center[2]);
	}
	else if (m_Orientation == CORONAL)
	{
		center[1] = CurrentPos[1];
		return  m_ROI.ContainsPoint(center[0], center[1], center[2]);

	}
	if (m_Orientation == SAGITTAL)
	{
		center[0] = CurrentPos[0];
		return  m_ROI.ContainsPoint(center[0], center[1], center[2]);

	}
	return false;

}
