#include "stdafx.h"
#include "PlanRepo.h"

#include "IDatasetManager.h"
#include "IPlanFactory.h"

using namespace parcast;
std::weak_ptr<IPlan> PlanRepo::Get(std::string const & uid)
{
	for (auto const& plan : m_Plans)
		if (plan->GetUID() == uid)
			return plan;

	return {};
}

void PlanRepo::Delete(std::string const& uid)
{
	auto relRepo = m_PackagePlanRelRepo.lock();
	if (relRepo)
		relRepo->DeleteByPlanUid(uid);
	auto newEnd = std::remove_if(m_Plans.begin(), m_Plans.end(), [&uid](auto &plan) {return plan->GetUID() == uid; });
	m_Plans.erase(newEnd, m_Plans.end());
}

std::weak_ptr<IPlan> PlanRepo::CreateNewPlan(std::string const& parentImageUid)
{
	auto factory = m_PlanFactory.lock();
	if (factory)
	{
		m_Plans.push_back(factory->CreateNewPlan(parentImageUid));
		return m_Plans.back();
	}
	
	return{};
}

void PlanRepo::SetPlanFactory(std::weak_ptr<IPlanFactory> factory)
{
	m_PlanFactory = factory;
}

void PlanRepo::SetPackagePlanRelRepo(std::weak_ptr<IPackagePlanRelRepo> relRepo)
{
	m_PackagePlanRelRepo = relRepo;
}

std::vector<std::weak_ptr<IPlan>> PlanRepo::GetAllPlans() const
{
	auto plans = std::vector<std::weak_ptr<IPlan>>();
	for (auto const& plan : m_Plans)
		plans.push_back(plan);
	return plans;
}

void PlanRepo::Clear()
{
	auto relRepo = m_PackagePlanRelRepo.lock();
	for (auto const& plan : m_Plans)
		relRepo->DeleteByPlanUid(plan->GetUID());

	m_Plans.clear();
}

