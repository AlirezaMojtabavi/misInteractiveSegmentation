#pragma once

enum  misLandmarkType
{
	GeneralSeed,
	ForeGroundSeed,
	BackGroundSeed,
	BiopsyTargetSeed,
	BiopsyEntrySeed,
	RegistrationErrorCorresponded,
	SurfaceRegistrationLandmark,
	SkinLandmark,
	BoneLandmark,
	TeethLandmark,
	MeasurmentLandmark,
	CheckPointSeed,
	TargetPointSeed,
	FixedLandmark,
	MovingLandmark,
	UnkownLandmarkType
};

enum LandmarkStatus//PositionStatus
{
	ValidPoint,
	InvalidPoint,
	InactivePoint,
	InCaptering
};

enum  LANDMARKLABELSTAUS
{
	NORMAL,
	SELECTED,
	UNDERCAPTURE
};

enum LANDMARKLABLETYPE
{
	NUMERICALLANDMARK,
	CHECKLANDMARK,
	ENTRYLANDMARK,
	TARGETLANDMARK,
	POINTLANDMARK,
	CAPTUREPOINTLANDMARK
};
