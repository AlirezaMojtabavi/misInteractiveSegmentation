#include "StdAfx.h"
#include "misPlanData.h"

#include "IPackagePlanRelRepo.h"
#include "IPlanRepo.h"
#include "ITransform.h"
#include "misStringTools.h"
#include "BusinessEntities\Point.h"
#include "ICoordinateSystemCorrelationManager.h"
#include "IPlanTransformCalculator.h"
#include "ITransformFactory.h"

misPlanData::misPlanData(
	const std::string& parentImageUid,
	std::weak_ptr<parcast::IPackagePlanRelRepo> pkgPlanRelRepo,
	std::weak_ptr<ICoordinateSystemCorrelationManager<std::string>> correlationManager,
	std::weak_ptr<parcast::IPlanTransformCalculator> planTranformCalculator,
	std::weak_ptr<parcast::ITransformFactory> tranformFactory,
	std::weak_ptr<parcast::IPlanRepo> planRepo, double targetRegionRadius, double screwDiameter)
	:m_ParentImageUID(parentImageUid),
	m_PkgPlanRelRepo(pkgPlanRelRepo),
	m_CorrelationManager(correlationManager),
	m_PlanTransformCalculator(planTranformCalculator),
	m_TransformFactory(tranformFactory),
	m_PlanRepo(planRepo),
m_TargetRegionRadius(targetRegionRadius),
m_ScrewDiameter(screwDiameter)
{
	m_DataObjectUID = misStringTools::GenerateNewUID();

	const auto getTransCalc = m_PlanTransformCalculator.lock();
	const auto getTransFactory = m_TransformFactory.lock();
	auto getCorrelationManager = m_CorrelationManager.lock();

	if (!(getTransCalc && getTransFactory && getCorrelationManager))
		throw std::exception("Some dependencies are not met...");

	auto transAndLen = getTransCalc->FromPlanPointsWithStartTranslation(
		parcast::Point<double, 3>{0., 0., 0.},
		parcast::Point<double, 3>{0., 0., 1.});

	m_PlanLength = transAndLen.PlanLength;
	const auto transform = getTransFactory->Create(transAndLen.CoordSysTransform.data());
	getCorrelationManager->SetTransform(m_DataObjectUID, m_ParentImageUID, transform);
}

double misPlanData::GetPlanCentricViewAngle() const
{
	return m_CentricViewAngle;
}

void misPlanData::SetPlanCentricViewAngle(const double& angle)
{
	m_CentricViewAngle = angle;
}

misUID misPlanData::GetParentImageUID() const
{
	return m_ParentImageUID;
}

misColorStruct misPlanData::GetPlannigColor()
{
	return m_PlannigColor;
}

void misPlanData::DeepCopy(misPlanData* planData)
{
	if (!planData)
		return;

	m_ParentImageUID = planData->GetParentImageUID();
	m_PlannigColor = planData->GetPlannigColor();
	m_PlanName = planData->GetPlanName();
	m_DataObjectUID = planData->GetUID();
	m_ValidEntry = planData->m_ValidEntry;
	m_ValidTarget = planData->m_ValidTarget;
	SetEntryPoint(planData->GetEntryPoint());
	SetTargetPoint(planData->GetTargetPoint());
	m_ScrewDiameter = planData->GetScrewDiameter();
	m_ScrewSourceType = planData->GetScrewSourceType();
	m_ScrewInterationType = planData->GetScrewInterationType();
}

void misPlanData::DeletePlan()
{
	auto relRepo = m_PkgPlanRelRepo.lock();
	if (relRepo)
		relRepo->DeleteByPlanUid(m_DataObjectUID);

	auto planRepo = m_PlanRepo.lock();
	if (planRepo)
		planRepo->Delete(m_DataObjectUID);
}

void misPlanData::SetTargetRegionRadius(double radius)
{
	m_TargetRegionRadius = radius;
}

double misPlanData::GetTargetRegionRadius() const
{
	return m_TargetRegionRadius;
}

double misPlanData::GetLength() const
{
	return m_PlanLength;
}

void misPlanData::SetTransform(const parcast::Point<double, 3>& entry, const parcast::Point<double, 3>& target)
{
	auto transformCalculator = m_PlanTransformCalculator.lock();
	auto transformFactory = m_TransformFactory.lock();
	auto correlationManager = m_CorrelationManager.lock();

	if (!(transformCalculator && transformFactory && correlationManager))
	{
		return;
	}

	auto transAndLen = transformCalculator->FromPlanPointsWithStartTranslation(entry, target);
	m_PlanLength = transAndLen.PlanLength;
	auto transform = transformFactory->Create(transAndLen.CoordSysTransform.data());
	correlationManager->SetTransform(m_DataObjectUID, m_ParentImageUID, transform);
}

parcast::Point<double, 3> misPlanData::GetPointFromTransform(const PointType type)
{
	auto getTransCalc = m_PlanTransformCalculator.lock();
	auto getCorrelationManager = m_CorrelationManager.lock();
	if (!(getTransCalc && getCorrelationManager))
	{
		if (type == PointType::Entry)
			return parcast::Point<double, 3>{0., 0., 0.};
		else
			return parcast::Point<double, 3>{0., 0., 1.};
	}
	auto transform = getCorrelationManager->GetTransform(m_DataObjectUID, m_ParentImageUID);
	auto transMatrixElement = std::vector<double>(16);
	transform->GetTransform()->GetMarixElements(transMatrixElement.data());
	auto getPoints = getTransCalc->FromTransform(transMatrixElement, m_PlanLength);
	if (type == PointType::Entry)
		return getPoints.Start;
	else
		return getPoints.End;
}

parcast::Point<double, 3> misPlanData::GetTargetPoint()
{
	return GetPointFromTransform(PointType::Target);
}

void misPlanData::SetTargetPoint(const parcast::Point<double, 3>& point)
{
	m_ValidTarget = true;
	SetTransform(GetEntryPoint(), point);
}

std::shared_ptr<const ITransform> misPlanData::GetTransform()
{
	auto getCorrelationManager = m_CorrelationManager.lock();

	if (!getCorrelationManager)
		return{};

	auto computedCorr = getCorrelationManager->GetTransform(m_DataObjectUID, m_ParentImageUID);
	return computedCorr->GetTransform();
}

bool misPlanData::GetEntryValidity()
{
	return m_ValidEntry;
}

bool misPlanData::GetTargetValidity()
{
	return m_ValidTarget;
}

bool misPlanData::GetPlanValidity()
{
	return GetEntryValidity() && GetTargetValidity();
}

void misPlanData::ResetTargetPoint()
{
	m_ValidTarget = false;
}

void misPlanData::ResetEntryPoint()
{
	m_ValidEntry = false;
}

void misPlanData::ResetPlan()
{
	ResetTargetPoint();
	ResetEntryPoint();
}

parcast::Point<double, 3> misPlanData::GetEntryPoint(void)
{
	return GetPointFromTransform(PointType::Entry);
}

void misPlanData::SetEntryPoint(const parcast::Point<double, 3>& point)
{
	m_ValidEntry = true;
	SetTransform(point, GetTargetPoint());
}

std::vector<std::shared_ptr<parcast::IPackagePlanRel>> misPlanData::GetPackageRels()
{
	auto relRepo = m_PkgPlanRelRepo.lock();
	if (relRepo)
		return relRepo->GetByPlanUid(m_DataObjectUID);
	return{};
}

std::string misPlanData::GetPlanName()
{
	return m_PlanName;
}

void misPlanData::SetPlanName(std::string planName)
{
	m_PlanName = planName;
}

std::string misPlanData::GetUID() const
{
	return m_DataObjectUID;
}

void misPlanData::SetUID(const std::string& id)
{
	m_DataObjectUID = id;
}

void misPlanData::SetScrewDiameter(double diameter)
{
	m_ScrewDiameter = diameter;
}

void misPlanData::SetScrewSourceType(ScrewWidgetSourceType srcType)
{
	m_ScrewSourceType = srcType;
}

void misPlanData::SetScrewInterationType(ScrewWidgetInteractionType interactionType)
{
	m_ScrewInterationType = interactionType;
}

ScrewWidgetSourceType misPlanData::GetScrewSourceType()
{
	return m_ScrewSourceType;
}

ScrewWidgetInteractionType misPlanData::GetScrewInterationType()
{
	return m_ScrewInterationType;
}

double misPlanData::GetScrewDiameter()
{
	return m_ScrewDiameter;
}