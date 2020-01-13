#include "StdAfx.h"
#include "misCoaxialToriCollection.h"

#include "misException.h"
#include "misMathUtils.h"

misCoaxialToriCollection::misCoaxialToriCollection(void)
	
{
	CreateTori();
	m_position[0] = 0;;
	m_position[1] = 0;
}

misCoaxialToriCollection::~misCoaxialToriCollection(void)
{
}

void misCoaxialToriCollection::UpdateRepresentation()
{
	double unitZ[] = { 0, 0, 1 };
	vtkSmartPointer<vtkTransform> transform = misMathUtils::RotationTransformFromVectors(unitZ, m_DestinationDirectionVector);
	transform->PostMultiply();
	transform->Translate(m_DestinationPosition[0], m_DestinationPosition[1], m_DestinationPosition[2]);

	std::for_each(m_Tori.begin(), m_Tori.end(), [&](std::shared_ptr<misTorus> torus){ 
		torus->GetTorusActor()->SetPosition(m_position);
	});
}

void misCoaxialToriCollection::SetProperties( const misCoaxialToriCollectionProperties &newSettings )
{
	m_Properties = newSettings;
	CreateTori();
}

const misCoaxialToriCollectionProperties & misCoaxialToriCollection::GetProperties() const
{
	return m_Properties;
}

void misCoaxialToriCollection::CreateTori()
{
	auto numberOfTori = m_Properties.GetNumberOfTori();
	auto crossSectionRadius = m_Properties.GetCrossSectionRadius();
	auto ringRadiusIncrementSize = m_Properties.GetRingRadiusIncrementSize();
	auto ringsSeparation = m_Properties.GetRingsSeparation();
	auto smallestRingRadius = m_Properties.GetSmallestRingRadius();
	auto XYPlaneDisplacement = m_Properties.GetXYPlaneDisplacement();
	auto toriColor = m_Properties.GetToriColour();
	
	m_Tori.clear();
	for (int i = 0; i < numberOfTori; i++)
	{
		std::shared_ptr<misTorus> torus(new misTorus(crossSectionRadius, smallestRingRadius + i * ringRadiusIncrementSize, 
			XYPlaneDisplacement + i * ringsSeparation));
		torus->GetTorusActor()->GetProperty()->SetColor(toriColor[0], toriColor[1], toriColor[2]);
		m_Tori.push_back(torus);
	}
}

const std::vector < std::shared_ptr<misTorus> > misCoaxialToriCollection::GetTori() const
{
	return m_Tori;
}

void misCoaxialToriCollection::SetPosition( const double* position )
{
	m_position[0] = position[0];
	m_position[1] = position[1];
}
