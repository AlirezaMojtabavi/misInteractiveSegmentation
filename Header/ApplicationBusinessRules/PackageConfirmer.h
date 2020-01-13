#pragma once
#include "IPackageConfirmer.h"

template < typename CST = std::string >
class ICoordinateSystemCorrelationManager;

namespace parcast
{

	class PackageConfirmer : public IPackageConfirmer
	{
	public:
		PackageConfirmer(std::shared_ptr< ICoordinateSystemCorrelationManager<std::string> > correlationManager);
		bool IsConfirmed(std::shared_ptr<ISimpleDataPackage> pkg) override;

	private:
		std::shared_ptr< ICoordinateSystemCorrelationManager<std::string> > m_CorrelationManager;
	};

}