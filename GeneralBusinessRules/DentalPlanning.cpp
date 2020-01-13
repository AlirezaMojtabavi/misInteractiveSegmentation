#include "stdafx.h"
#include "DentalPlanning.h"

#include "IPackageConfirmer.h"
#include "IPackagePlanRel.h"
#include "IPackagePlanRelRepo.h"
#include "IRootEntity.h"
#include "ISimpleDataPackage.h"
#include "ITreatmentSolution.h"
#include "IPlanRepo.h"

using namespace parcast;

DentalPlanning::DentalPlanning(
	std::shared_ptr<IDentalPlanningUiAdapter> uiAdapter,
	IRootEntity *rootEntity,
	std::shared_ptr<IPlanRepo> planRepo,
	std::shared_ptr<IPackageConfirmer> confirmer,
	std::weak_ptr<IPackagePlanRelRepo> packagePlanRelRepo) :
	m_UiAdapter(uiAdapter),
	m_RootEntity(rootEntity),
	m_PlanRepo(planRepo),
	m_PackageConfirmer(confirmer),
	m_PackagePlanRelRepo(packagePlanRelRepo)
{
}

std::vector<std::shared_ptr<ISimpleDataPackage>> DentalPlanning::GetConfirmedPackages()
{
	auto solution = m_RootEntity->GetCurrentSolution();
	auto packages = solution->GetPackages();
	auto confirmedPackages = decltype(packages)();

	for (auto const& pkg : packages)
		if (m_PackageConfirmer->IsConfirmed(pkg))
			confirmedPackages.push_back(pkg);

	return confirmedPackages;
}

void DentalPlanning::StartUp()
{
	auto confirmedPackages = GetConfirmedPackages();

	m_UiAdapter->UpdateList(confirmedPackages);
	m_UiAdapter->SetState(DentalPlanningStatus::Initial);

	if (!confirmedPackages.empty())
		m_UiAdapter->SelectPackage((!m_CurrentPackage) ? confirmedPackages[0] : m_CurrentPackage);
}

void parcast::DentalPlanning::SetCurrentPackage(std::shared_ptr<ISimpleDataPackage> pkg)
{
	m_CurrentPackage = pkg;
	m_UiAdapter->SetState(m_State = DentalPlanningStatus::ImageSelected);
	m_CurrentPlan.reset();
}

void parcast::DentalPlanning::SetCurrentPlan(std::shared_ptr<IPlan> plan)
{
	auto selectedPackageRel = plan->GetPackageRels().front();
	auto selectedPackage = selectedPackageRel->GetPackage();
	if (selectedPackage != m_CurrentPackage)
		m_UiAdapter->SelectPackage(selectedPackage);

	m_State = DentalPlanningStatus::PlanSelected;
	m_UiAdapter->SetState(DentalPlanningStatus::PlanSelected);

	m_CurrentPlan = plan;
	auto displayProps = selectedPackageRel->GetVisibility();
	auto indicators = PlanIndicators();
	indicators.PlanDiameter = plan->GetScrewDiameter();
	indicators.PlanCentricViewAngle = plan->GetPlanCentricViewAngle();
	indicators.Visibility = displayProps.GetVisibilityIn3DScene() && displayProps.visibilityIn2DScene;
	m_UiAdapter->UpdatePlanIndicators(indicators);
}

void parcast::DentalPlanning::CapturePoint(const parcast::Point<double, 3>& point)
{
	auto relRepo = m_PackagePlanRelRepo.lock();
	auto planRepo = m_PlanRepo.lock();
	if (!relRepo || !planRepo)
		return;

	if (m_State != DentalPlanningStatus::AddingPlan)
		return;

	auto plan = planRepo->CreateNewPlan(m_CurrentPackage->GetMainImage()->GetUID()).lock();
	auto planPkgRel = relRepo->Create(m_CurrentPackage, plan);
	mis3DModelObjectOpacityPropertiesStrct opacityProps;
	opacityProps.SetAllVisible();
	planPkgRel->SetVisibility(opacityProps);

	plan->SetEntryPoint(point);
	auto parcastPoint = parcast::Point<double, 3>(point[0], point[1], point[2] + 10);
	plan->SetTargetPoint(parcastPoint);
	std::ostringstream planName;
	planName << "Plan " << m_CurrentPackage->GetNumberOfPlanes();
	plan->SetPlanName(planName.str());
	plan->SetPlannigColor(misColorStruct(255, 255, 0, 1));
	plan->SetScrewDiameter(2.5);
	plan->SetScrewSourceType(ScrewWidgetSourceType::Line);
	plan->SetScrewInterationType(ScrewWidgetInteractionType::Free);
	auto confirmedPackages = GetConfirmedPackages();
	m_UiAdapter->UpdateList(confirmedPackages);
	m_UiAdapter->SelectPlan(plan, true);
}

void parcast::DentalPlanning::EnableAddPlanMode()
{
	if (m_CurrentPackage)
	{
		m_UiAdapter->SetState(m_State = DentalPlanningStatus::AddingPlan);
	}
}

void parcast::DentalPlanning::ModifyPlan(std::shared_ptr<IPlan> plan, const PointType& startPoint, const PointType& endPoint)
{
	plan->SetEntryPoint(startPoint);
	plan->SetTargetPoint(endPoint);
	m_UiAdapter->SelectPlan(plan, false);
}

void DentalPlanning::NewSpline()
{
	if (m_State != DentalPlanningStatus::ImageSelected)
		return;

	m_CurrentPackage->SetParametricSpline(std::vector<itk::Point<double, 3>>{});
	m_UiAdapter->SetState(m_State = DentalPlanningStatus::DrawingCurve);
}

void DentalPlanning::AcceptSpline(const SplinePoints& points)
{
	if(m_State != DentalPlanningStatus::DrawingCurve)
		return;

	m_CurrentPackage->SetParametricSpline(points);
	m_UiAdapter->SelectPackage(m_CurrentPackage);
}

void DentalPlanning::SetScrewDiameter(double diameter)
{
	if (m_State != DentalPlanningStatus::PlanSelected)
		return;

	m_CurrentPlan->SetScrewDiameter(diameter);
	m_UiAdapter->UpdatePlan(m_CurrentPlan);
}

void DentalPlanning::SetScrewVisiblity(bool isVisible)
{
	if (m_State != DentalPlanningStatus::PlanSelected)
		return;

	mis3DModelObjectOpacityPropertiesStrct visibility;
	isVisible ? visibility.SetAllVisible() : visibility.SetAllInvisible();
	m_CurrentPlan->GetPackageRels().front()->SetVisibility(visibility);
	m_UiAdapter->UpdatePlan(m_CurrentPlan);
}

void DentalPlanning::SetPlanCentricViewAngle(double angle)
{
	if (m_State != DentalPlanningStatus::PlanSelected)
		return;

	m_CurrentPlan->SetPlanCentricViewAngle(angle);
	m_UiAdapter->SetPlanCentricViewAngle(angle);
}

void DentalPlanning::DeletePlan()
{
	if (m_State != DentalPlanningStatus::PlanSelected)
		return;

	m_CurrentPlan->DeletePlan();
	m_UiAdapter->UpdateList(GetConfirmedPackages());
	m_UiAdapter->SelectPackage(m_CurrentPackage);
}
