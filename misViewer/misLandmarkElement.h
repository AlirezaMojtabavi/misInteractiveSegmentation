#pragma  once
#include "misLandmarkenums.h"
#include "itkPoint.h"

struct misLandmarkElement
{

	itk::Point<double, 3> position;
	LandmarkStatus   status;
	double           error;
	misLandmarkType  type;
	LANDMARKLABLETYPE label;
	void Reset(void)
	{
		position[0] = -1;
		position[1] = -1;
		position[2] = -1;

		status = LandmarkStatus::InvalidPoint;
		error = -1;
	};
	misLandmarkElement()
	{
		this->Reset();
	};
};
