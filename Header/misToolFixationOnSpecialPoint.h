#pragma once

#include "mistimepassingforaction.h"

class misToolFixationOnSpecialPoint :
	public misTimePassingForAction
{
public:
	misToolFixationOnSpecialPoint(void);
	~misToolFixationOnSpecialPoint(void);

protected:

	double		m_DesiredFixedPoint[3];

	
	double      m_MaxPermittedToolMovment;

protected:
	bool   CheckLastMovementValidity(double* newToolPosition);
	double ComputDistanse(double pos1[3], double pos2[3]);

public:
	double GetActionValue(void); // this is between 0-1  , 2 means it has reached to max and has not been reset
	void   SetToolPosition(double* newToolPosition);

	// must be called in the inherited class constructor
	void   UpdateAllSetting(misToolFixationPropertiesStr str);
	void   SetMaxPermittedMovementAssumeAsFixedTool(double movement);

	void SetDesiredFixedPoint(double* desiredFixedPoint, bool letChangePreviousfixPoint);
};

