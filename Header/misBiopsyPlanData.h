#pragma once
#ifndef misBiopsyPlanData_H
#define misBiopsyPlanData_H

#include "misPlanData.h"
#include "misSTRCT.h"

class  misBiopsyPlanData : public misPlanData
{
private:


public:
	static misBiopsyPlanData* New(void);

	void    DeepCopy(misPlanData* planData);
private:
	misBiopsyPlanData(void);
	~misBiopsyPlanData(void);
};
#endif