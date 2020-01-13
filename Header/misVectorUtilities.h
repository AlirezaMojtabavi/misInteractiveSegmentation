#pragma once

#include "misTrackingManagerEnums.h"

class misVectorUtilities
{
public:	
	// this is camera2OpenGL and also openGLToCamera coordinate
	static void ConvertCamera2OpenGLSpace(double point1[], double point2[]);

	// ConvertTrackerToOpenGLCoordinates is added to cover design obscurities of ConvertCamera2OpenGLSpace. It does the same
	// thing in a different, more predictable, less presumptuous manner.
	static itk::Vector<double, 3> ConvertTrackerToOpenGLCoordinates(
		const itk::Vector<double, 3> &trackerCoords, TrackerType trackerType);

	static void NormalizeVector(double vector[]);

protected:
	misVectorUtilities(void);
	~misVectorUtilities(void);
};

