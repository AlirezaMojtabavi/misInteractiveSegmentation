#pragma once

#include "misLibraryMacroes.h"

class MISLIBRARYEXPORT misTimerLog 
{
	vtkTimerLog * m_Timer;
	double m_Time;
	bool IsCounting;

public:
	misTimerLog(void);
	~misTimerLog(void);

	void Start();
	void Stop();
	void Reset();
	void Restart();
	double GetElapsedTime();
	bool IsStart();
};

