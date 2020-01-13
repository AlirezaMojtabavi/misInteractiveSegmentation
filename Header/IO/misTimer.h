#pragma once

#include "ITimer.h"

class misTimer : public ITimer
{
public:
	misTimer();

	virtual void Start();
	virtual void Stop();
	virtual void Reset();
	virtual double GetTime() const;

private:
	typedef boost::chrono::duration< double, boost::ratio<1, 1> > DoubleSeconds;
	typedef boost::chrono::high_resolution_clock ClockType;

	ClockType::time_point m_StartTime;
	ClockType::time_point m_StopTime;
	DoubleSeconds m_ValueAtStop;
	bool m_IsRunning;
};

