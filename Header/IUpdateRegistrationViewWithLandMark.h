#pragma once
#include "misobjectProperitiesEnums.h"
#include "ISimpleDataPackage.h"
#include "misVolumeViewingTypes.h"

class IUpdateRegistrationViewWithLandMark
{
public:
	virtual void UpdateViewWithLandMark(int index, std::shared_ptr<ISimpleDataPackage> package, bool subTabCompleteness) = 0;
	virtual ~IUpdateRegistrationViewWithLandMark() = default;
};