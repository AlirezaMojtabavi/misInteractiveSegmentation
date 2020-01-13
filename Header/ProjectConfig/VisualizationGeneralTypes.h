#pragma once

enum IMAGEORIENTATION
{
	AXIAL=0,
	CORONAL,
	SAGITTAL,
	VOLUME,
	PANORAMIC,
	UNKnownDirection,
};

enum MODELCURSOR
{
	CROSS = 0,
	SIMPLE
};
enum MEASURMENTMODE
{
	NORMALMEASURMENT = 0 ,
	AUTOMEASURMENT
};

enum FusionMoveDirection
{
	RIGHT = 0,
	LEFT,
	UP,
	DOWN,
	FORWARD, 
	BACKWARD
};

enum FusionRotateDirection
{
	CLOCKWISE = 0,
	COUNTER_CLOCKWISE
};

enum ViewPortType
{
	SAME = 0,
	MULTIPLE
};

struct FusionMoveDirectionStrct
{
	FusionMoveDirection fusionDir;
	int windowIndex;
};
struct FusionRotateDirectionStrct
{
	FusionRotateDirection fusionRot;
	int windowIndex;
};