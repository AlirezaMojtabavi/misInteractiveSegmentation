#pragma once
#include "vtkTimerLog.h"
#include "misToolFixationAnalysis.h"


class misTakeAutomaticSnapShot : public misToolFixationAnalysis
{
public:
	void SetActivation( bool value );
	void UpdateSettingFromAppSetting(void);

	misTakeAutomaticSnapShot(void);
	~misTakeAutomaticSnapShot(void);	
};

