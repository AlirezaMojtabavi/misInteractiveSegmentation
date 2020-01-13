#pragma once
#include "mislandMarkPosAndStatusStr.h"
#include "ProjectConfig\misSubSequenseGeneralStateEnums.h"

class ILandmarkRegistrationUIAdapter
{
public:
	virtual void UpdateGUI(std::vector<mislandMarkPosAndStatusStr> movables,
		bool lastMustBeSelected,
		int currentSelectedLandmarkIndex, bool subTabCompleteness,
		subSequenseGeneralStateEnums trackingState) = 0;
	virtual void UpdateLandmarkErrorListInGUI(std::vector<mislandMarkPosAndStatusStr>& landmarks,
		bool m_LastMustBeSelected, int m_CurrentSelectedLandmarkIndex) = 0;
	virtual ~ILandmarkRegistrationUIAdapter() = default;
};