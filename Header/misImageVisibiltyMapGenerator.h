#pragma once
#include "ISimpleDataPackage.h"
#include "misPlaneContrast.h"

class misImageVisibilityMapGenerator
{
public:
	misImageVisibilityMapGenerator(std::shared_ptr<ISimpleDataPackage>);
	std::map<misPlaneEnum, bool> GetVisibilityMap() const;
private:
	std::shared_ptr<ISimpleDataPackage> m_CurrentPackage;
	std::map<misPlaneEnum, bool> m_VisibilityMap;;
};

