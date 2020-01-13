#pragma once
#include "misStrctColorData.h"
#include "misVertebraEnum.h"


struct ScrewPlanInformation
{
	std::string					 planName;
	double						 transarency;
	misColorStruct				 color;
 	misVertebraScrewDirectionEnum ScrewVerbetraDirection;
 	misVertebraNameEnum			 ScrewVerbetraPosition;
	double						 ScrewDiameter;
	double						 ScrewLength;
};		   

struct ScrewPlanPropertyIndicator
{
	misUID objectUID;
	misUID objectContainerUID;
	ScrewPlanInformation		planProperty;
	ScrewWidgetInteractionType	screwInteractionType;
	ScrewWidgetSourceType		screwSourceType;
};

 