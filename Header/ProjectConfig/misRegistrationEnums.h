#pragma once
#include "misLandmarkenums.h"


enum misLandmarkBasedRegistrationCalculationType
{
	IndependentLandmarks,
	SecondLandIsDependentOnTheFirst,
	unSetLandmarkType
};

enum  RegistrationResult
{
	PointSizeError,
	CollinearityError,
	SuccessRegistration, 
	UnkownRegisrationError
};

//enum misLandmarkType
//{
//	skinLamdmark,
//	boneLandmark,
//	internalLandmark,
//	unKownLandmarkType
//};




enum misLandmarkRegistarationPlaySoundStatus
{
	NoSound,
	MeanError,
	CurrentLandmarkError
};
