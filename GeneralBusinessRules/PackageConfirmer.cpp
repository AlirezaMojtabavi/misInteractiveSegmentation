#include "stdafx.h"
#include "PackageConfirmer.h"

#include "ICoordinateSystemCorrelationManager.h"
#include "ISimpleDataPackage.h"

using namespace parcast;

PackageConfirmer::PackageConfirmer(std::shared_ptr< ICoordinateSystemCorrelationManager<std::string> > correlationManager)
	:m_CorrelationManager(correlationManager)
{
}

bool parcast::PackageConfirmer::IsConfirmed(std::shared_ptr<ISimpleDataPackage> pkg)
{
	pkg->SetCSCorrelationManager(m_CorrelationManager);
	bool isConfirmed = true;
	if (pkg->GetObjectType() == misHybridPackageType)
	{
		auto getImages = pkg->GetImages();
		for (const auto& image : getImages)
			isConfirmed &= image->GetConfirmedDirection();
	}
	else
		isConfirmed = false;
	return isConfirmed;
}
