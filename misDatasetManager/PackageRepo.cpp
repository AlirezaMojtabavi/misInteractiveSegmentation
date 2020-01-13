#include "stdafx.h"
#include "PackageRepo.h"

#include "IDatasetManager.h"
#include "ISimpleDataPackage.h"

using namespace parcast;

PackageRepo::PackageRepo()
{
}

std::shared_ptr<ISimpleDataPackage> PackageRepo::Get(const std::string& packageUid) const
{
	for (auto const& pkg : m_Packages)
		if (pkg->GetObjectUID() == packageUid)
			return pkg;

	return {};
}

PackageRepo::PackageListType PackageRepo::GetBySolutionId(const std::string& solutionId) const
{
	return m_Packages;
}

PackageRepo::PackageListType& PackageRepo::GetPackageDataSForDatasetManager()
{
	return m_Packages;
}
