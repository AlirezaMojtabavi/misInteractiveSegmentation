#pragma once

#include "misTimePassingForActionPropertiesStr.h"

class misTimePassingForAction
{
public:
	misTimePassingForAction(void);
	~misTimePassingForAction(void);

	virtual bool   GetActivation(void);	
	virtual double GetActionValue(void);  // this is between 0-1  , 2 means it has reached to max and has not been reset
	// must be updated in the inherited class constructor
	virtual void   UpdateAllSetting(misTimePassingForActionPropertiesStr setting) ;


	void   Reset(void);


	void   SetActivation(bool value) ;
	void   SetTimeForActing(double time);


protected:
	vtkTimerLog*  m_Timer;
	double        m_ElapsedTime;
	double        m_ValidTimeForAction;
	int           m_Counter;
	double        m_ActionValue; // this a ration between 0-1                              // 1 is a time you must do simthing
	bool          m_ActOnLastPosition;
	bool          m_ActivationStatus;


protected:
		void   UpdateElapsedTime(void);
		void   ResetTimer(void);


};

