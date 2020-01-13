#pragma once

#include "misColorStruct.h"
#include "misSimplePointType.h"
#include "misTypes.h"

enum misVertebraNameEnum 
{
	C1,
	C2,
	C3,
	C4,
	C5,
	C6,
	C7,
	T1,
	T2,
	T3,
	T4,
	T5,
	T6,
	T7,
	T8,
	T9,
	T10,
	T11,
	T12,
	L1,
	L2,
	L3,
	L4,
	L5,
	S1,
	S2,
	N1,
	N2,
	N3,
	N4,
	N5,
	N6,
	N7,
	N8,
	unSetVertebraName
};

enum misVertebraScrewDirectionEnum
{
	RightVertbra,
	LeftVertbra,
	UpRight,
	UpLeft,
	DownRight,
	DownLeft,
	unSetScreLocation
};

enum misImplanteBrandnamesEnum
{
	StrykerImplants,
	GenerelImaplants
};

enum ScrewWidgetInteractionType
{
	Extend = 0, 
	Rotation, 
	Position, 
	Free
};

enum ScrewWidgetSourceType 
{
	Line = 0, 
	Screw
};


