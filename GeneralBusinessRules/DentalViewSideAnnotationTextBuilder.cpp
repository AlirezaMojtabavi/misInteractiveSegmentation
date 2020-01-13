#include "stdafx.h"
#include "DentalViewSideAnnotationTextBuilder.h"

using namespace parcast;

void DentalViewSideAnnotationTextBuilder::SetViewerType(ViewerType viewerType)
{
	m_ViewerType = viewerType;
}

void DentalViewSideAnnotationTextBuilder::SetHasCurve(bool hasCurve)
{
	m_HasCurve = hasCurve;
}

void DentalViewSideAnnotationTextBuilder::SetDentalQuadrant(DentalQuadrant quadrant)
{
	m_Quadrant = quadrant;
}

SideAnnotations DentalViewSideAnnotationTextBuilder::GetSideAnnotations() const
{
	return Annotations.at({ m_HasCurve, m_Quadrant, m_ViewerType });
}

DentalViewSideAnnotationTextBuilder::DentalViewSideAnnotationTextBuilder()
	: Annotations
{
	{ {false, DentalQuadrant::UpperRight, ViewerType::Axial}, { "R", "P", "L", "A" } },
	{ {false, DentalQuadrant::UpperRight, ViewerType::Coronal}, { "R", "I", "L", "S" } },
	{ {false, DentalQuadrant::UpperRight, ViewerType::Sagittal}, { "P", "I", "A", "S" } },
	{ {false, DentalQuadrant::UpperLeft, ViewerType::Axial}, { "R", "P", "L", "A" } },
	{ {false, DentalQuadrant::UpperLeft, ViewerType::Coronal}, { "R", "I", "L", "S" } },
	{ {false, DentalQuadrant::UpperLeft, ViewerType::Sagittal}, { "P", "I", "A", "S" } },
	{ {false, DentalQuadrant::LowerLeft, ViewerType::Axial}, { "R", "A", "L", "P" } },
	{ {false, DentalQuadrant::LowerLeft, ViewerType::Coronal}, { "R", "I", "L", "S" } },
	{ {false, DentalQuadrant::LowerLeft, ViewerType::Sagittal}, { "P", "I", "A", "S" } },
	{ {false, DentalQuadrant::LowerRight, ViewerType::Axial}, { "R", "A", "L", "P" } },
	{ {false, DentalQuadrant::LowerRight, ViewerType::Coronal}, { "R", "I", "L", "S" } },
	{ {false, DentalQuadrant::LowerRight, ViewerType::Sagittal}, { "P", "I", "A", "S" } },
	{ {true, DentalQuadrant::UpperRight, ViewerType::Axial}, { "R", "P", "L", "A" } },
	{ {true, DentalQuadrant::UpperRight, ViewerType::Coronal}, { "D", "I", "M", "S" } },
	{ {true, DentalQuadrant::UpperRight, ViewerType::Sagittal}, { "L", "I", "B", "S" } },
	{ {true, DentalQuadrant::UpperLeft, ViewerType::Axial}, { "R", "P", "L", "A" } },
	{ {true, DentalQuadrant::UpperLeft, ViewerType::Coronal}, { "M", "I", "D", "S" } },
	{ {true, DentalQuadrant::UpperLeft, ViewerType::Sagittal}, { "L", "I", "B", "S" } },
	{ {true, DentalQuadrant::LowerLeft, ViewerType::Axial}, { "R", "A", "L", "P" } },
	{ {true, DentalQuadrant::LowerLeft, ViewerType::Coronal}, { "M", "I", "D", "S" } },
	{ {true, DentalQuadrant::LowerLeft, ViewerType::Sagittal}, { "L", "I", "B", "S" } },
	{ {true, DentalQuadrant::LowerRight, ViewerType::Axial}, { "R", "A", "L", "P" } },
	{ {true, DentalQuadrant::LowerRight, ViewerType::Coronal}, { "D", "I", "M", "S" } },
	{ {true, DentalQuadrant::LowerRight, ViewerType::Sagittal}, { "L", "I", "B", "S" } }
}
{
}