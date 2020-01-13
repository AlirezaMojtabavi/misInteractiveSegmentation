#pragma once
#include "misPackageViewingItemsStrct.h"
#include "ICoordinateSystemCorrelationManager.h"
#include "ISimpleDataPackage.h"
#include "PackageListViewingType.h"
#include "IConfirmedImageCounter.h"

class misViewableElement
{
public:
	misViewableElement(const std::vector<std::shared_ptr<ISimpleDataPackage>> packges,
		const std::shared_ptr<ICoordinateSystemCorrelationManager<std::string>>
		coordinateSystemCorrelationManagerSCorrelationManager, std::shared_ptr<IConfirmedImageCounter>);
 
	std::vector< misPackageViewingItemsStrct > GetPackageViewingList(PackageListViewingType viewingType);
private:
	const std::vector<std::shared_ptr<ISimpleDataPackage>> m_Packges;
	const  std::shared_ptr< ICoordinateSystemCorrelationManager<std::string> > m_CSCorrelationManager;
	std::shared_ptr<IConfirmedImageCounter> m_Counter;
};

