#pragma once
#include "misLandmarkElement.h"

//The ILandmarksManager class provide functionality for Adding , removing , or updating landmark in viewers, 
class ILandmarksManager
{
public:
	virtual void AddLandmark( misLandmarkElement landmark) = 0;
	//update in landmark properties at index 
	virtual void UpdateLandmark(int index, misLandmarkElement landmark) = 0;
	//remove landmark from list
	virtual void RemoveLandmark( int index) = 0;
	//return position of landmark position at index
	virtual void LandmarkCaptureEnable(bool enable) = 0;
	virtual itk::Point<double, 3>	GetLandmarkPosition(int index) const = 0;
	virtual void HideLandmarks() = 0;
	virtual void ShowLandmarks() = 0;
	virtual void ResetLandMarks( void ) = 0 ;
};
