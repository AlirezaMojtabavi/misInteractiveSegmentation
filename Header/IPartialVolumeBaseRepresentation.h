#pragma once

#include "mis3dRepresentation.h"
#include "voreen/misCroppingDirectionInVR.h"

class IPartialVolumeBaseRepresentation
{
	
public:
	//igstkStandardClassBasicTraitsMacro(misPartialVolumeBaseRepresentation,misOldObject);

	virtual void SetToolPosition(double xCoord, double yCoord, double zCoord)=0;
	virtual void SetToolAngle(float toolAngle)=0;
	virtual void SetCroppingDirection( misCroppingDirectionInVR direction)=0;
 };

