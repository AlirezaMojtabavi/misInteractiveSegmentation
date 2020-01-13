#include "stdafx.h"
#include "BusinessEntities/LandmarkColor.h"

using namespace parcast;

misDoubleColorStruct LandmarkColor::GetColor(misLandmarkType landmarkType, LANDMARKLABELSTAUS status)
{
	misDoubleColorStruct greenColor;
	greenColor.SetColorToGreen();

	misDoubleColorStruct resultColor;
	resultColor.Alpha = 1.0;
	switch (landmarkType)
	{
	case(GeneralSeed):
	case(SkinLandmark):
	case(CheckPointSeed):
	case(FixedLandmark):
	case(BoneLandmark):
	{
		resultColor = greenColor;
		if (status == NORMAL || status == UNDERCAPTURE)
		{
			resultColor.Red = 14.0 / 255.0;
			resultColor.Green = 80.0 / 255.0;
			resultColor.Blue = 34.0 / 255.0;
		}
		break;
	}
	case(SurfaceRegistrationLandmark):
	case(MeasurmentLandmark):
	case(ForeGroundSeed):
	{
		resultColor = greenColor;
		break;
	}
	case(BackGroundSeed):
	case(TargetPointSeed):
	case(MovingLandmark):
	{
		resultColor.Red = 1.0;
		resultColor.Green = 1.0;
		resultColor.Blue = 0;
		break;
	}
	case(BiopsyTargetSeed):
	case(BiopsyEntrySeed):
	{
		resultColor.Red = 1.0;
		resultColor.Green = 0.0;
		resultColor.Blue = 1.0;
		break;
	}
	case(RegistrationErrorCorresponded):
	{
		resultColor.Red = 1.0;
		resultColor.Green = 0.0;
		resultColor.Blue = 0.0;
		break;
	}
	}
	return resultColor;
}