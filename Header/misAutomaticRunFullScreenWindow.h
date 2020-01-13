#pragma once

#include "misTimePassingForActionPropertiesStr.h"

class misAutomaticRunFullScreenWindow
{
	vtkTimerLog*  m_Timer;
	double        m_ElapsedTime;
	double        m_TimeForGoingToFullScreen;
	double        m_GotoFullScreen; // this a ration between 0-1
	                               // 1 is a time you must go to full screen
	bool          m_Activation;
	bool          m_GotoFullScreenTimer;
	int           m_Counter;


private:
	void   UpdateElapsedTime(void);

public:
	void   Reset(void);
	void   UpdateAllSetting(misTimePassingForActionPropertiesStr setting);

	void   SetActivation(bool value);
	bool   GetActivation(void);

	double GetTimer(void);
	void   SetTimeForGoingToFullScreen(double time);
	
    misAutomaticRunFullScreenWindow(void);
   ~misAutomaticRunFullScreenWindow(void);
};

