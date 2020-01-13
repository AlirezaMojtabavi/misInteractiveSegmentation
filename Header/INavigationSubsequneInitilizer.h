#pragma once
#include "ISimpleDataPackage.h"
class INavigationSubsequenceInitializer
{
public :
	virtual ~INavigationSubsequenceInitializer() = default;
	virtual void Start(std::shared_ptr<ISimpleDataPackage> m_CurrentPackage, bool freezeState) = 0;
};
