#pragma once
#include "ISimpleDataPackage.h"
#include "IVolumeCropping.h"

class IUpdateLayoutToDynamicLayout
{
public:
	virtual ~IUpdateLayoutToDynamicLayout() = default;
	virtual void Update(const std::string& layout, double VisibilityMarginInAnatomicalPlanesDirection, bool freezeState,
	                    std::shared_ptr<ISimpleDataPackage> package, std::shared_ptr<IVolumeCropping>) = 0;

};
