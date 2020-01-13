#include "stdafx.h"
#include "..\Header\misCameraMacher.h"


misCameraMacher::misCameraMacher()
{
}


misCameraMacher::~misCameraMacher()
{
}

bool misCameraMacher::NearlyIsEqual(misCamera source, misCamera dest)
{
	const  double m_MinimumDistanceChangeForUpdatingCameraPosition = 0.99;


	auto newPosition = source.GetPosition();
	auto prevPosition = dest.GetPosition();
	bool  positionChanged = (abs(prevPosition[0] - newPosition[0]) > m_MinimumDistanceChangeForUpdatingCameraPosition) ||
		(abs(prevPosition[1] - newPosition[1]) > m_MinimumDistanceChangeForUpdatingCameraPosition) ||
		(abs(prevPosition[2] - newPosition[2]) > m_MinimumDistanceChangeForUpdatingCameraPosition);


	auto newFocal = source.GetFocal();
	auto prevFocal = dest.GetFocal();
	const  double m_MinimumDistanceChangeForUpdatingCameraFocal = 0.99;

	bool  focalChanged = (abs(prevFocal[0] - newFocal[0]) > m_MinimumDistanceChangeForUpdatingCameraFocal) ||
		(abs(prevFocal[1] - newFocal[1]) > m_MinimumDistanceChangeForUpdatingCameraFocal) ||
		(abs(prevFocal[2] - newFocal[2]) > m_MinimumDistanceChangeForUpdatingCameraFocal);

	const  double m_MinimumDistanceChangeForUpdatingCameraViewUp = 0.99;

	auto  viewVector = source.GetViewUp();
	auto  prevUpvector = dest.GetViewUp();
	bool viewUpChnaged = (abs(viewVector[0] - viewVector[0]) > m_MinimumDistanceChangeForUpdatingCameraViewUp) ||
		(abs(viewVector[1] - viewVector[1]) > m_MinimumDistanceChangeForUpdatingCameraViewUp) ||
		(abs(viewVector[2] - viewVector[2]) > m_MinimumDistanceChangeForUpdatingCameraViewUp);
	return !(positionChanged|| focalChanged || viewUpChnaged);
}
