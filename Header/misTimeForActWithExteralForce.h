#pragma once

#include "misTimePassingForAction.h"

class misTimeForActWithExteralForce :	public misTimePassingForAction
{
private:
	bool m_ExternalForce;

public:
	misTimeForActWithExteralForce(void);
	~misTimeForActWithExteralForce(void);

	void SetExternalForceForAction(bool action);
	bool GetExternalForceForAction( void);
	void Reset(void);

	// Over written functions
	bool   GetActivation(void);	
	double GetActionValue(void); 
};

