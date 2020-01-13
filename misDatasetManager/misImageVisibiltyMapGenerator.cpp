#include "stdafx.h"
#include "misImageVisibiltyMapGenerator.h"
#include "misPlaneContrast.h"


misImageVisibilityMapGenerator::misImageVisibilityMapGenerator(std::shared_ptr<ISimpleDataPackage> package)
	:m_CurrentPackage(package)
{
	m_VisibilityMap = [&]
	{
		std::map<misPlaneEnum, bool> visibilityMap;
		for (auto index = 0; index < m_CurrentPackage->GetImageDataDependencies().size(); index++)
		{
			visibilityMap[static_cast<misPlaneEnum>(index)] = m_CurrentPackage->GetImageDataDependencies()[index]->GetVisibility();
		}
		return visibilityMap;
	}();

}

std::map<misPlaneEnum, bool> misImageVisibilityMapGenerator::GetVisibilityMap()const
{
	return m_VisibilityMap;
}

