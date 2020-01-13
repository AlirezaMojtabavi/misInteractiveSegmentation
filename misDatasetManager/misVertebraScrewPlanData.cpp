#include "StdAfx.h"
#include "misVertebraScrewPlanData.h"

#include "misStringTools.h"

misVertebraScrewPlanData::misVertebraScrewPlanData(
	const std::string& parentImageUid,
	std::weak_ptr<parcast::IPackagePlanRelRepo> pkgPlanRelRepo,
	std::weak_ptr<ICoordinateSystemCorrelationManager<std::string>> correlationManager,
	std::weak_ptr<parcast::IPlanTransformCalculator> planTranformCalculator,
	std::weak_ptr<parcast::ITransformFactory> tranformFactory,
	std::weak_ptr<parcast::IPlanRepo> planRepo,
	double targetRegionRadius, double screwDiameter)
	:misPlanData(parentImageUid, pkgPlanRelRepo, correlationManager, planTranformCalculator, tranformFactory, planRepo, targetRegionRadius, screwDiameter),
	m_ScrewPlacementFinalized(false)
{
	m_PlannigColor.SetGrayColor();
}

misVertebraScrewPlanData::~misVertebraScrewPlanData(void)
{
}

void misVertebraScrewPlanData::DeepCopy(std::weak_ptr<misPlanData> screwPlanData)
{
	if (auto screwPlanDataLocked = screwPlanData.lock())
	{
		misPlanData::DeepCopy(screwPlanDataLocked.get());

		std::weak_ptr<misVertebraScrewPlanData> screwPlan = std::dynamic_pointer_cast<misVertebraScrewPlanData>(screwPlanDataLocked);
		if (auto screwPlanLocked = screwPlan.lock())
		{
			m_ScrewVerbetraDirection = screwPlanLocked->GetScrewVerbetraDirection();
			m_ScrewVerbetraPosition = screwPlanLocked->GetScrewVerbetraPosition();
			m_ImplantBrand = screwPlanLocked->GetImplantBrand();
			m_ScrewLength = screwPlanLocked->GetScrewLength();
			m_ScrewPlacementFinalized = screwPlanLocked->GetScrewPlacementFinalized();
		}
	}
}



void misVertebraScrewPlanData::SetScrewPlacementFinalized(bool isFinished)
{
	m_ScrewPlacementFinalized = isFinished;
}

bool misVertebraScrewPlanData::GetScrewPlacementFinalized()
{
	return  m_ScrewPlacementFinalized;
}

MisObjectType misVertebraScrewPlanData::GetObjectType(void)
{
	return misScrewPlanDataType;
}

misVertebraScrewDirectionEnum misVertebraScrewPlanData::GetScrewVerbetraDirection()
{
	return m_ScrewVerbetraDirection;
}

misVertebraNameEnum misVertebraScrewPlanData::GetScrewVerbetraPosition()
{
	return m_ScrewVerbetraPosition;
}

misImplanteBrandnamesEnum misVertebraScrewPlanData::GetImplantBrand()
{
	return m_ImplantBrand;
}


double misVertebraScrewPlanData::GetScrewLength()
{
	return m_ScrewLength;
}

void misVertebraScrewPlanData::SetScrewVerbetraDirection(misVertebraScrewDirectionEnum loc)
{
	m_ScrewVerbetraDirection = loc;
}

void misVertebraScrewPlanData::SetScrewVerbetraPosition(misVertebraNameEnum pos)
{
	m_ScrewVerbetraPosition = pos;
}

void misVertebraScrewPlanData::SetImplantBrand(misImplanteBrandnamesEnum brand)
{
	m_ImplantBrand = brand;
}

void misVertebraScrewPlanData::SetScrewLength(double len)
{
	m_ScrewLength = len;
}

