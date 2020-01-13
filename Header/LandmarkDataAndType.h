#pragma once
#include <misLandmarkenums.h>

struct LandmarkDataAndType
{
	boost::optional<unsigned int> m_currentLandmarkIndex;
	misLandmarkType m_CurrentLandmarkType = UnkownLandmarkType;
	LANDMARKLABLETYPE m_CurrentLandmarkLableType = NUMERICALLANDMARK;
	bool m_CaptureLandmark = false;
};
