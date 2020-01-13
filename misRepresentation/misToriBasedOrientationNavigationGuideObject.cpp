#include "StdAfx.h"
#include "misToriBasedOrientationNavigationGuideObject.h"

#include "misException.h"

misToriBasedOrientationNavigationGuideObject::misToriBasedOrientationNavigationGuideObject(void)
{
	AddTorusProps();
}

misToriBasedOrientationNavigationGuideObject::~misToriBasedOrientationNavigationGuideObject(void)
{
}

void misToriBasedOrientationNavigationGuideObject::UpdateRepresentation()
{
	if (!GetNavigationState() || !GetNavigationState()->IsInitialized())
		throw misException("misOrientationNavigationGuideObject not properly initialized. NavigationState null.");

	double toolNormalDirection[3];	// T
	std::copy(GetNavigationState()->GetToolNormalDirection(), 
		GetNavigationState()->GetToolNormalDirection() + 3, toolNormalDirection);

	double planNormalDirection[3];	// P
	GetNavigationState()->CalculatePlanNormalDirection(planNormalDirection);

	m_ToriCollectionForTool.SetDestinationDirectionVector(toolNormalDirection);
	m_ToriCollectionForTool.SetDestinationPosition(GetNavigationState()->GetToolTipPosition());
	m_ToriCollectionForPlan.SetDestinationDirectionVector(planNormalDirection);
	m_ToriCollectionForPlan.SetDestinationPosition(GetNavigationState()->GetPlanStartPoint());
	m_ToriCollectionForTool.UpdateRepresentation();
	m_ToriCollectionForPlan.UpdateRepresentation();
}

void misToriBasedOrientationNavigationGuideObject::SetProperties(
	const misToriBasedOrientationNavigationGuideObjectProperties &newSettings)
{
	m_Properties = newSettings;
	ClearProps();

	m_ToriCollectionForPlan.SetProperties(newSettings.GetToriCollectionPropertiesForPlan());
	m_ToriCollectionForTool.SetProperties(newSettings.GetToriCollectionPropertiesForTool());

	AddTorusProps();
}

void misToriBasedOrientationNavigationGuideObject::AddTorusProps()
{
	auto planTori = m_ToriCollectionForPlan.GetTori();
	std::for_each(planTori.begin(), planTori.end(), [this] (std::shared_ptr<misTorus> torus) {
		AddProp(torus->GetTorusActor());
	});

	auto toolTori = m_ToriCollectionForTool.GetTori();
	std::for_each(toolTori.begin(), toolTori.end(), [this] (std::shared_ptr<misTorus> torus) {
		AddProp(torus->GetTorusActor());
	});
}
