#pragma once

#include "misTimePassingForAction.h"
#include "misitkTypdef.h"

class vtkTimerLog;


class misToolFixationAnalysis: public misTimePassingForAction
{
	enum positionNameEnum
	{
		lastPoint,
		lastCapturedPoint
	};

public:

	misToolFixationAnalysis(void);
	~misToolFixationAnalysis(void);

	double GetActionValue(void); // this is between 0-1  , 2 means it has reached to max and has not been reset
	void   SetToolPosition(const double* newToolPosition);
	void   SetToolPositionToPreventCaptureIt(double* newPosition);  // this position assumed as as a captured position and will not capture as a current position

	// must be called in the inherited class constructor
	void   UpdateAllSetting(misToolFixationPropertiesStr str) ;
	void   SetMaxPermittedMovementAssumeAsFixedTool(double movement);


protected:

	double        m_LastAcceptedPosition[3];
	double        m_lastPosition[3];
	double        m_NewPosition[3];

	double        m_ValidTimeForAction;
	double        m_MaxPermittedToolMovment;

protected:
	bool   CheckLastMovementValidity(positionNameEnum  positionName);
	void   UpdateLastPosition(void);
	void   UpdateLastCapturedPosition(void);
	double ComputDistanse(double pos1[3], double pos2[3]);

	
};

