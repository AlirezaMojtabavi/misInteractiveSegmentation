#include "stdafx.h"
#include "PackagePlanRelRepo.h"

#include "ISimpleDataPackage.h"

using namespace parcast;


void PackagePlanRelRepo::SetRelFactory(std::shared_ptr<IPackagePlanRelFactory> relFactory)
{
	m_RelFactory = relFactory;
}

std::shared_ptr<IPackagePlanRel> parcast::PackagePlanRelRepo::Create(
	std::shared_ptr<ISimpleDataPackage> package, std::shared_ptr<IPlan> plan)
{
	auto pkgUid = package->GetObjectUID();
	auto planUid = plan->GetUID();
	auto key = std::make_pair(pkgUid, planUid);
	if (m_Table.find(key) == m_Table.cend())
	{
		m_Table[key] = m_RelFactory->Create(pkgUid, planUid);
		return m_Table[key];
	}
	return{};
}

std::vector<std::shared_ptr<IPackagePlanRel>> parcast::PackagePlanRelRepo::GetByPlanUid(const std::string& planUid) const
{
	auto result = std::vector<std::shared_ptr<IPackagePlanRel>>();
	for(auto const &row : m_Table)
		if (row.first.second == planUid)
			result.push_back(row.second);
	return result;
}


std::vector<std::shared_ptr<parcast::IPackagePlanRel>> parcast::PackagePlanRelRepo::GetByPackageUid(const std::string& packageUid) const
{
	auto result = std::vector<std::shared_ptr<IPackagePlanRel>>();
	for (auto const &row : m_Table)
		if (row.first.first == packageUid)
			result.push_back(row.second);
	return result;
}

template<typename T> void parcast::PackagePlanRelRepo::EraseIfOnMap(T& condition)
{
	for (auto it = m_Table.begin(); it != m_Table.end(); )
		if (condition(it))
			it = m_Table.erase(it);
		else
			++it;
}

void parcast::PackagePlanRelRepo::DeleteByPackageUid(const std::string& uid)
{
	EraseIfOnMap([&uid](auto it) {return it->first.first == uid;});
}


void parcast::PackagePlanRelRepo::Delete(const std::string& pkgUid, const std::string& planUid)
{
	EraseIfOnMap([&pkgUid, &planUid](auto it) {return it->first.first == pkgUid && it->first.second == planUid;});
}

void parcast::PackagePlanRelRepo::DeleteByPlanUid(const std::string& uid)
{
	EraseIfOnMap([&uid](auto it) {return it->first.second == uid; });
}

std::shared_ptr<parcast::IPackagePlanRel> parcast::PackagePlanRelRepo::Get(const std::string& pkgUid, const std::string& planUid) const
{
	auto key = std::pair<std::string, std::string>(pkgUid, planUid);
	
	if (m_Table.find(key) != m_Table.cend())
		return m_Table.at(key);

	return {};
}
