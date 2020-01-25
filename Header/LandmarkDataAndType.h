#pragma once
#include <misLandmarkenums.h>

class LandmarkDataAndType
{
public:
	void SetCurrentLandmarkIndex(unsigned int index)
	{
		m_CurrentLandmarkIndex = index;
	}
	boost::optional<unsigned int> GetCurrentLandmarkIndex()const
	{
		return m_CurrentLandmarkIndex;
	}
	void ResetLandmarkIndex()
	{
		m_CurrentLandmarkIndex.reset();
	}
	misLandmarkType m_CurrentLandmarkType = UnkownLandmarkType;
	LANDMARKLABLETYPE m_CurrentLandmarkLableType = NUMERICALLANDMARK;
	bool m_CaptureLandmark = false;
private:
	boost::optional<unsigned int> m_CurrentLandmarkIndex;
};
