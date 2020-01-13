#include "stdafx.h"
#include "PlanFactory.h"
#include "misVertebraScrewPlanData.h"
#include <misApplicationSetting.h>
using namespace parcast;

PlanFactory::PlanFactory(std::weak_ptr<IPackagePlanRelRepo> relRepo,
	std::weak_ptr<ICoordinateSystemCorrelationManager<std::string>> correlationManager,
	std::weak_ptr<parcast::IPlanTransformCalculator> planTranformCalculator,
	std::weak_ptr<parcast::ITransformFactory> tranformFactory,
	std::weak_ptr<parcast::IPlanRepo> planRepo)
	:
	m_RelRepo(relRepo),
	m_corrManager(correlationManager),
	m_PlanTranformCalculator(planTranformCalculator),
	m_TranformFactory(tranformFactory),
	m_PlanRepo(planRepo)
{
}

std::shared_ptr<IPlan> PlanFactory::CreateNewPlan(std::string  const& parentImageUid)
{
	const auto planTargetRadius =
		misApplicationSetting::GetInstance()->GetSettingsContainer()->GetDouble("misPlanningSetting/PlanTargetRadius");
	const auto planScrewDiameter =
		misApplicationSetting::GetInstance()->GetSettingsContainer()->GetDouble("misPlanningSetting/PlanDiameter");

	return std::make_shared<misVertebraScrewPlanData>(
		parentImageUid, m_RelRepo, m_corrManager, m_PlanTranformCalculator, m_TranformFactory, m_PlanRepo, planTargetRadius, planScrewDiameter);
}
