#pragma once

#include "misitkTypdef.h"
#include "misLandmarkenums.h"

struct misLandmarkPointStrct
{
	misItkPointType   position;
	misItkVectorType  direction;
	misLandmarkType     pointType;

	inline static double  EuclideanDistance(misLandmarkPointStrct point1, misLandmarkPointStrct point2)
	{
		double distance, PowerDist;
		PowerDist = pow(point1.position[0] - point2.position[0], 2) + pow(point1.position[1] - point2.position[1], 2) + pow(point1.position[2] - point2.position[2], 2);
		distance = sqrt(PowerDist);
		return distance;
	}

	misLandmarkPointStrct()
	{
		this->Reset();
	}

	void Reset()
	{
		position[0] = -1;
		position[1] = -1;
		position[2] = -1;

		direction[0] = -1;
		direction[1] = -1;
		direction[2] = -1;

		pointType = UnkownLandmarkType;
	}

};

typedef std::vector<misLandmarkPointStrct> misLandmarkListTypdef;





