#pragma once

#include "IPackageRepo.h"

class ISimpleDataPackage;

namespace parcast
{

	class PackageRepo : public IPackageRepo
	{
	public:
		using PackageListType = std::vector< std::shared_ptr<ISimpleDataPackage> >;

		PackageRepo();

		std::shared_ptr<ISimpleDataPackage> Get(const std::string& packageUid) const override;
		PackageListType GetBySolutionId(const std::string& solutionId) const override;
		
		PackageListType& GetPackageDataSForDatasetManager();

	private:
		PackageListType m_Packages;
	};
}
