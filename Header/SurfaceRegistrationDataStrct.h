#pragma once

struct SurfaceRegistrationDataStrct
{
	int NumberOfPreviousLandmarks = 0;
	int NumberOfNewLandmarks = 0;
	double Error = -1.0;
	double lastLandmarkError = -1.0;
	bool lastlandmarkValidity = false;
};

